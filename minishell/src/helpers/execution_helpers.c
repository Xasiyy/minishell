/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:25:48 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/29 11:35:29 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirect to child process (dup2 to stdout)
void	setup_child_pipes(int fd_in, int *pipe_fd)
{
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			cleanup_and_exit(fd_in, pipe_fd);
		safe_close(&fd_in);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		cleanup_and_exit(fd_in, pipe_fd);
	safe_close(&pipe_fd[0]);
	safe_close(&pipe_fd[1]);
}

// Execute cmd in child
void	child_process(t_command *cmd, char **env, int *exit_status)
{
	t_shell	*shell;

	shell = get_shell_context(NULL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->args))
	{
		execute_builtin(cmd->args, exit_status);
		free_shell(shell, 1);
		exit(*exit_status);
	}
	else
		execute_child(cmd, env);
	free_shell(shell, 1);
	exit(*exit_status);
}

// Redirect to parent process (dup2 to stdin)
void	setup_parent_pipes(int fd_out, int *pipe_fd)
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		cleanup_and_exit(fd_out, pipe_fd);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		cleanup_and_exit(fd_out, pipe_fd);
	safe_close(&fd_out);
	safe_close(&pipe_fd[0]);
	safe_close(&pipe_fd[1]);
}

static void	wait_child(int *exit_status)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	handle_parent_process(pid, &status, exit_status);
}

// Manage a parent process for a cmd
void	parent_process(t_command *cmd, char **env, int *exit_status)
{
	pid_t	pid;
	t_shell	*shell;

	shell = get_shell_context(NULL);
	if (cmd->args && cmd->args[0] && ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd->args, shell), (void)0);
	if (is_builtin(cmd->args) && is_safe_in_executed_parent(cmd->args[0])
		&& is_safe_in_parent(cmd))
	{
		execute_builtin_redirection(cmd, exit_status);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		*exit_status = 1;
		return ;
	}
	if (pid == 0)
		child_process(cmd, env, exit_status);
	else
		wait_child(exit_status);
}
