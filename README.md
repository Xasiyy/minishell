# Minishell — Réimplémentation d'un shell Unix en C

Minishell est un projet réalisé dans le cadre du cursus **42**. L'objectif : recréer un shell Unix fonctionnel inspiré de Bash, capable de lire des commandes, de les parser, de gérer les pipes, les redirections, les heredocs, l'expansion de variables, et d'exécuter des binaires via `execve`. Le tout sans fuite mémoire, avec une seule variable globale autorisée pour la gestion des signaux.

---

## Architecture du projet

```
minishell/
├── include/
│   └── minishell.h                      # Structures & prototypes globaux
├── src/
│   ├── main/
│   │   └── main.c                       # Point d'entrée, init t_shell
│   ├── shell_main/
│   │   └── shell_main.c                 # Boucle principale readline
│   ├── line_handler/
│   │   └── line_handler.c               # Chef d'orchestre du traitement
│   ├── parsing/
│   │   ├── parsing.c                    # Entrée du parsing
│   │   ├── parsing_entry.c              # Dispatch lexer → pipeline
│   │   ├── parsing_tok.c / parsing_tokens.c  # Tokenisation
│   │   ├── parsing_syntax.c             # Vérification syntaxique
│   │   ├── split_pipeline.c             # Découpage sur les pipes
│   │   ├── split_quotes.c               # Découpage en respectant les quotes
│   │   ├── segmentation_quotes.c        # Gestion des zones protégées
│   │   ├── expander.c                   # Expansion $VAR, $?
│   │   ├── parsing_redirection.c        # Identification des redirections
│   │   ├── parsing_add_redirection.c    # Construction des t_redir
│   │   ├── parsing_pipeline.c           # Construction des t_pipeline
│   │   ├── parsing_field_splitting.c    # Découpage post-expansion
│   │   ├── parsing_check.c              # Validations diverses
│   │   ├── parsing_trim.c               # Nettoyage des tokens
│   │   └── parsing_utils.c              # Helpers du parsing
│   ├── execution/
│   │   ├── execution.c                  # Dispatch simple / pipeline
│   │   ├── execution_child.c            # Logique du processus fils
│   │   ├── execve_handler.c             # Résolution du chemin + execve
│   │   ├── pipeline.c                   # Fork & pipe pour commandes chaînées
│   │   ├── redirections.c               # Gestion des redirections (dup2)
│   │   └── child_utils.c                # Utilitaires des processus fils
│   ├── builtins/
│   │   ├── builtins_core.c              # Dispatcher des builtins
│   │   ├── builtins_echo.c              # echo (option -n)
│   │   ├── builtins_cd.c                # cd
│   │   ├── builtins_env.c               # env / pwd
│   │   ├── builtins_export.c            # export
│   │   ├── builtins_exit.c              # exit
│   │   ├── builtins_exit_parent_child.c # Distinction parent/enfant pour exit
│   │   ├── builtins_utils.c             # Helpers des builtins
│   │   └── heredoc.c                    # Lecture heredoc (<< delimiter)
│   ├── env/
│   │   ├── env_entry.c                  # Init & copie de l'environnement
│   │   ├── env_display.c                # Affichage (env, export)
│   │   ├── env_unset.c                  # Suppression de variables
│   │   └── env_utils.c                  # Recherche & modification
│   ├── signal/
│   │   └── signals.c                    # Gestionnaires SIGINT / SIGQUIT
│   ├── context_env/
│   │   └── context_env.c                # Contexte d'exécution (env passé à execve)
│   ├── command_path/
│   │   └── command_path.c               # Résolution du PATH
│   ├── free/
│   │   ├── free_shell.c                 # Libération de t_shell
│   │   ├── free_heredoc.c               # Libération des heredocs
│   │   ├── free_utils.c                 # Libération des structures parsing
│   │   ├── memory_utils.c               # Wrappers malloc/free sécurisés
│   │   ├── safe_close.c                 # Fermeture sécurisée des fd
│   │   └── clean_and_exit.c             # Nettoyage complet avant sortie
│   ├── helpers/
│   │   ├── env_helpers.c                # Accès rapide aux variables d'env
│   │   └── execution_helpers.c          # Helpers d'exécution
│   └── utils/
│       ├── file_utils.c                 # Utilitaires fichiers
│       └── ft_strdup_array.c            # Duplication de tableaux de strings
├── libft/                               # Bibliothèque C personnelle
├── ft_printf/                           # Implémentation de printf
├── get_next_line/                       # Lecture ligne par ligne
└── Makefile
```

---

## Fonctionnement général

Le flux d'exécution complet, de la saisie au retour au prompt :

```
main()
  └── start_shell_loop()
        └── readline() → "cmd1 | cmd2 > out.txt"
              └── handle_line()
                    ├── lexer()                    → liste de tokens
                    ├── split_pipeline_tokens()    → séparation sur les pipes
                    ├── parse_all_pipelines()      → commandes avec redirections
                    └── execute_all_pipelines()
                          ├── pipeline simple  → execute_single_command()
                          └── pipeline complexe → execute_pipeline()
                                └── execute_command()
                                      ├── handle_redirections()
                                      └── builtin ou execve()
```

---

## Phase de parsing

Le parsing est l'une des grosses parties du projet. Elle se déroule en plusieurs étapes distinctes et ordonnées.

### 1. Tokenisation (Lexer)

Le lexer parcourt la ligne caractère par caractère et produit une liste de `t_token`. Chaque token porte une information sur son type (mot, opérateur, pipe, redirection) et sur son contexte de quoting — information essentielle pour les étapes suivantes.

Les quotes sont gérées dès cette étape :
- les **quotes simples** protègent intégralement leur contenu (aucune expansion)
- les **quotes doubles** protègent leur contenu sauf le caractère `$`

### 2. Vérification syntaxique

Avant tout traitement, la syntaxe est validée. Les cas d'erreur détectés incluent notamment les pipes ou redirections mal placés, les opérateurs consécutifs, ou les tokens vides là où un argument est attendu.

Exemples de cas rejetés :
```
| cmd          → pipe en début de ligne
cmd | | cmd    → pipe consécutifs
echo >         → redirection sans cible
echo >>>       → opérateur invalide
```

### 3. Expansion des variables

L'expansion est appliquée sur les tokens qui ne sont pas dans des quotes simples :

- `$VAR` et `${VAR}` → valeur dans l'environnement du shell
- `$?` → code de retour de la dernière commande (`shell->last_exit_status`)
- À l'intérieur de quotes simples → aucune expansion

### 4. Construction des structures

Après expansion, les tokens sont transformés en structures exploitables par l'exécution :

- **`t_token`** : unité lexicale brute
- **`t_redir`** : une redirection (type + fichier cible)
- **`t_command`** : une commande avec ses `args` et sa liste de `t_redir`
- **`t_pipeline`** : un tableau de `t_command` représentant une chaîne de pipes

---

## Phase d'exécution

### Commande simple

Pour une commande sans pipe, `execute_single_command()` :
1. applique les redirections avec `handle_redirections()`
2. détermine si c'est un builtin avec `is_builtin()`
3. si oui, l'exécute directement dans le processus parent (pour `cd`, `exit`, `export`, `unset`) ou dans un fork (pour `echo`, `pwd`, `env` si redirection présente)
4. si non, résout le chemin via `PATH` et appelle `execve()`

### Pipeline

Pour une chaîne de commandes séparées par des pipes, `execute_pipeline()` :
1. crée un `pipe()` entre chaque paire de commandes
2. fork chaque commande dans un processus fils
3. chaque fils reçoit `stdin` du pipe précédent et écrit dans le pipe suivant via `dup2()`
4. tous les descripteurs inutiles sont fermés dans chaque processus
5. le parent attend tous ses fils avec `waitpid()` et récupère le dernier code de retour

### Redirections

| Opérateur | Comportement |
|---|---|
| `<` | Ouvre le fichier en lecture, redirige `stdin` |
| `>` | Ouvre le fichier en écriture (troncature), redirige `stdout` |
| `>>` | Ouvre le fichier en écriture (append), redirige `stdout` |
| `<<` | Heredoc : lecture jusqu'au délimiteur, écrit dans un pipe temporaire |

Pour le heredoc, chaque ligne est lue via `readline()` jusqu'à la rencontre du délimiteur. Si le délimiteur était entre quotes lors du parsing, l'expansion est désactivée dans le corps du heredoc.

---

## Builtins implémentées

Toutes les builtins sont réimplémentées sans appel à des programmes externes.

| Builtin | Comportement |
|---|---|
| `echo` | Affiche les arguments. Option `-n` supprime le saut de ligne final |
| `cd` | Change de répertoire, met à jour `PWD` et `OLDPWD` dans l'environnement |
| `pwd` | Affiche le répertoire courant |
| `export` | Ajoute ou modifie une variable d'environnement |
| `unset` | Supprime une variable d'environnement |
| `env` | Affiche l'environnement courant |
| `exit` | Quitte le shell avec le code fourni en argument |

---

## Gestion des signaux

Une seule variable globale est utilisée dans tout le projet : `g_signal_received`, un `int` qui stocke le numéro du dernier signal reçu.

| Signal | Comportement |
|---|---|
| `Ctrl-C` (SIGINT) | Affiche un nouveau prompt en mode interactif, interrompt proprement un heredoc en cours |
| `Ctrl-D` | EOF détecté par `readline()` → quitte le shell proprement |
| `Ctrl-\` (SIGQUIT) | Ignoré en mode interactif |

Les processus fils reçoivent le comportement par défaut du système pour SIGINT, afin de ne pas perturber l'exécution des commandes externes.

---

## Gestion mémoire

La gestion mémoire a fait l'objet d'un travail rigoureux tout au long du projet. Toutes les structures allouées dynamiquement sont libérées après chaque cycle d'exécution :

- `free_tokens()` après le parsing
- `free_pipeline()` après l'exécution
- `free_shell()` à la fermeture

Le projet passe valgrind sans fuite mémoire (hors fuites internes à `readline`, autorisées par le sujet). Un fichier `valgrind.supp` est fourni pour filtrer ces fuites connues lors des tests.

---

## Contrôles

| Touche | Action |
|---|---|
| Saisie clavier | Entrée libre des commandes |
| `Fleche haut/bas` | Navigation dans l'historique (readline) |
| `Ctrl-C` | Interrompt la commande courante, affiche un nouveau prompt |
| `Ctrl-D` | Quitte le shell |
| `Ctrl-\` | Ignoré |

---

## Compilation & lancement

### Prérequis

- GCC / Clang
- `readline` installée (`libreadline-dev` sur Debian/Ubuntu)
- Make

### Compilation

```bash
make
```

### Lancement

```bash
./minishell
```

### Nettoyer

```bash
make clean    # supprime les .o
make fclean   # supprime les .o et l'exécutable
make re       # recompile entièrement
```

---

## Gestion des erreurs

Le shell affiche des messages d'erreur conformes à Bash dans les cas suivants :

- erreur de syntaxe (`unexpected token`, pipe mal placé, redirection vide)
- commande introuvable → `minishell: command: not found`
- fichier introuvable → `No such file or directory`
- permission refusée → `Permission denied`
- mauvais argument à `exit` → `exit: numeric argument required`
- quotes non fermées → erreur détectée dès la tokenisation

---

## Ressources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [The Open Group — Shell & Utilities](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- Sujet officiel 42 

---

## Auteure

Projet réalisé en binôme dans le cadre du cursus **42** — School of Computer Science.
