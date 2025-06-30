/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:30:03 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/28 17:42:37 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cree processus pr executer 2 commande relie par un pipe
void	exec_cmds(t_files files, int pipe_fd[2], t_command *cmd, char **env)
{
	pid_t	pid;
	int		exit_status;

	(void)files;
	(void)pipe_fd;
	pid = fork();
	if (pid < 0)
		clean_and_exit(get_shell_context(NULL), EXIT_FAILURE);
	if (pid == 0)
	{
		child_process(cmd, env, &exit_status);
		_exit(exit_status);
	}
	waitpid(pid, NULL, 0);
}

// Configure et gere lexecution d un pipeline de commandes
void	minishell(t_files files, char *input, char **env)
{
	t_shell		*shell;
	int			pipe_fd[2];
	int			status;
	t_command	*cmd;

	shell = get_shell_context(NULL);
	cmd = parsing(input, shell);
	remove_empty_args(cmd);
	if (pipe(pipe_fd) == -1)
		clean_and_exit(shell, EXIT_FAILURE);
	exec_cmds(files, pipe_fd, cmd, env);
	safe_close(&pipe_fd[0]);
	safe_close(&pipe_fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(EXIT_FAILURE);
}
