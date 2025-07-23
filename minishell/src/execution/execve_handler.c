/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:45:12 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 14:12:14 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Displays and handles Permission denied error (code 126)
static void	print_perm_denied(t_command *cmd, t_shell *shell)
{
	ft_eprintf("minishell: %s: Permission denied\n", cmd->args[0]);
	free_shell(shell, 1);
	_exit(126);
}

// Displays and handles command not found error (code 127)
static void	print_not_found(t_command *cmd, t_shell *shell)
{
	ft_eprintf("minishell: %s: command not found\n", cmd->args[0]);
	free_shell(shell, 1);
	_exit(127);
}

// Displays and handles the no such file or directory error (code 127)
static void	print_no_such_file(t_command *cmd, t_shell *shell)
{
	ft_eprintf("minishell: %s: no such file or directory\n", cmd->args[0]);
	free_shell(shell, 1);
	_exit(127);
}

// Displays and handles Is a directory error (code 126)
static void	print_is_dir(t_command *cmd, t_shell *shell)
{
	ft_eprintf("minishell: %s: Is a directory\n", cmd->args[0]);
	free_shell(shell, 1);
	_exit(126);
}

// Handles all errors returned by execve()
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
