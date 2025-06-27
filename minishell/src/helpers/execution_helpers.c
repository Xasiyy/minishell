/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:25:48 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/17 16:49:57 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirection ds le processus enfant (dup2 vers stdout)
void	setup_child_pipes(int fd_in, int *pipe_fd)
{
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			cleanup_and_exit(fd_in, pipe_fd);
		close(fd_in);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		cleanup_and_exit(fd_in, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

// Execute cmd ds le processus enfant
void	child_process(t_command *cmd, char **env, int *exit_status)
{
	t_shell	*shell;

	(void)env;
	shell = get_shell_context(NULL);
	if (is_builtin(cmd->args))
		execute_builtin(cmd->args, exit_status);
	else
		execute_external(cmd, shell->env->envp, exit_status);
	free_shell(shell, 1);
	exit(*exit_status);
}

// Redicrection ds le processus parent (dup2 vers stdin)
void	setup_parent_pipes(int fd_out, int *pipe_fd)
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		cleanup_and_exit(fd_out, pipe_fd);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		cleanup_and_exit(fd_out, pipe_fd);
	close(fd_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

// Attend la fin d un processus enfant
static void	wait_child(int *exit_status)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else
		*exit_status = 1;
}

// Gere un processus parent pr une cmd
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
