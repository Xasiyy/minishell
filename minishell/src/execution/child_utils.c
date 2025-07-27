/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmailc.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:47:47 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/27 18:09:59 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Configure redirections, duplicate the correct descriptors,
// then execute the command in the child process
void	fork_and_run_child(t_command *cmd, char **env, int prev_fd,
		int pipe_fd[2])
{
	t_shell	*shell;
	int		local_status;

	shell = get_shell_context(NULL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		safe_close(&prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		safe_close(&pipe_fd[0]);
		safe_close(&pipe_fd[1]);
	}
	if (handle_redirections(cmd) == -1)
	{
		free_shell(shell, 1);
		exit(1);
	}
	local_status = 0;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->args))
		execute_command(cmd, env, &local_status);
	else
	{
		execute_child(cmd, env);
		local_status = 1;
	}
	free_shell(shell, 1);
	_exit(local_status);
}

// Creates a communication tube with error checking
void	create_pipe(int *pipe_fd)
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

// Create a new process with fork()
pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		handle_error("fork");
	}
	return (pid);
}
