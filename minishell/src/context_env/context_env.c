/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:01:11 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/27 17:42:54 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Pr stocker ou recuperer le contexte global du shell
t_shell	*get_shell_context(t_shell *set_shell)
{
	static t_shell	*ctx = NULL;

	if (set_shell != NULL)
		ctx = set_shell;
	return (ctx);
}

// Retrouver le pointeur vers le shell a partir d un champ env et t_shell
t_shell	*get_shell_from_env(t_env *env)
{
	static t_shell	*shell_ptr = NULL;

	if (env == NULL)
		return (shell_ptr);
	shell_ptr = (t_shell *)((char *)env - offsetof(t_shell, env));
	return (shell_ptr);
}

// Compte le nmbr de chaînes ds un tableau de chaînes (ex: envp)
static int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// Copie les variables d'environnement dans une structure t_env
t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	int		count;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	count = count_env(envp);
	env->envp = malloc(sizeof(char *) * (count + 1));
	if (!env->envp)
		return (free_env(env), NULL);
	i = 0;
	while (envp[i])
	{
		env->envp[i] = ft_strdup(envp[i]);
		if (!env->envp[i])
			return (free_env(env), NULL);
		i++;
	}
	env->envp[i] = NULL;
	return (env);
}
