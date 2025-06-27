/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:45:12 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/17 16:12:35 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Affiche et gère l’erreur Permission denied (code 126)
static void	print_perm_denied(t_command *cmd, t_shell *shell)
{
	ft_eprintf("minishell: %s: Permission denied\n", cmd->args[0]);
	free_shell(shell, 1);
	_exit(126);
}

// Affiche et gère l’erreur command not found (code 127)
static void	print_not_found(t_command *cmd, t_shell *shell)
{
	ft_eprintf("minishell: %s: command not found\n", cmd->args[0]);
	free_shell(shell, 1);
	_exit(127);
}

// Affiche et gère l’erreur no such file or directory (code 127)
static void	print_no_such_file(t_command *cmd, t_shell *shell)
{
	ft_eprintf("minishell: %s: no such file or directory\n", cmd->args[0]);
	free_shell(shell, 1);
	_exit(127);
}

// Affiche et gère l’erreur Is a directory (code 126)
static void	print_is_dir(t_command *cmd, t_shell *shell)
{
	ft_eprintf("minishell: %s: Is a directory\n", cmd->args[0]);
	free_shell(shell, 1);
	_exit(126);
}

// Gère toutes les erreurs retournées par execve()
void	handle_execve_errors(t_command *cmd, int via_path_search)
{
	t_shell	*shell;

	shell = get_shell_context(NULL);
	if (errno == EACCES || errno == EPERM)
		print_perm_denied(cmd, shell);
	else if (errno == ENOENT)
	{
		if (via_path_search)
			print_not_found(cmd, shell);
		else
			print_no_such_file(cmd, shell);
	}
	else if (errno == EISDIR)
		print_is_dir(cmd, shell);
	perror("execve");
	free_shell(shell, 1);
	_exit(1);
}
