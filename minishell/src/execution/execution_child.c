/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:02 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/20 15:53:44 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <sys/stat.h>

// Vérifie si une chaîne contient un '/'
static int	contains_slash(const char *s)
{
	while (*s)
	{
		if (*s++ == '/')
			return (1);
	}
	return (0);
}

// Résout le chemin de la commande (avec ou sans PATH)
char	*resolve_command_path(t_command *cmd, char **env)
{
	if (!cmd || !cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		return (NULL);
	if (cmd->path)
		return (cmd->path);
	if (contains_slash(cmd->args[0]))
		cmd->path = ft_strdup(cmd->args[0]);
	else
		cmd->path = find_command_in_path(cmd->args[0], env);
	return (cmd->path);
}

// Résout le chemin de la commande (avec ou sans PATH)
void	exit_cmd_not_found(t_shell *shell)
{
	ft_eprintf("minishell: command not found\n");
	free_shell(shell, 1);
	_exit(127);
}

// Quitte avec code 126 si la commande est un dossier
static void	exit_is_directory(char *path, t_shell *shell)
{
	ft_eprintf("minishell: %s: Is a directory\n", path);
	free_shell(shell, 1);
	_exit(126);
}

// Exécute une commande dans un processus enfan
void	execute_child(t_command *cmd, char **env)
{
	struct stat	st;
	int			via_path;
	t_shell		*shell;

	shell = get_shell_context(NULL);
	if (cmd->redirections && handle_redirections(cmd) == -1)
		_exit(EXIT_FAILURE);
	if ((!cmd->args || !cmd->args[0]
			|| cmd->args[0][0] == '\0') && cmd->heredoc)
		_exit(0);
	via_path = !contains_slash(cmd->args[0]);
	cmd->path = resolve_command_path(cmd, env);
	if (!cmd->path)
	{
		ft_eprintf("minishell: %s: command not found\n", cmd->args[0]);
		free_shell(shell, 1);
		_exit(127);
	}
	if (stat(cmd->path, &st) == 0 && S_ISDIR(st.st_mode))
		exit_is_directory(cmd->path, shell);
	execve(cmd->path, cmd->args, env);
	handle_execve_errors(cmd, via_path);
}
