/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:36:17 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/20 16:02:42 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Lance tts les commandes de la pipeline en créant un processus pr chacune
void	execute_pipeline(t_pipeline *pipeline, char **env)
{
	t_command	*cmd;
	t_shell		*shell;
	int			prev_fd;
	pid_t		last_pid;
	pid_t		pid;

	last_pid = -1;
	shell = get_shell_context(NULL);
	shell->env->envp = env;
	prev_fd = -1;
	cmd = pipeline->commands;
	while (cmd)
	{
		prev_fd = execute_child_process(cmd, env, prev_fd, &pid);
		if (cmd->next == NULL)
			last_pid = pid;
		cmd = cmd->next;
	}
	wait_for_all_children(shell, last_pid);
}

// Gère la création du pipe, le fork, et appelle la f qui exécute le fils
int	execute_child_process(t_command *cmd, char **env, int prev_fd,
		pid_t *pid_out)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	setup_pipe(pipe_fd, cmd);
	pid = fork();
	if (pid == 0)
		fork_and_run_child(cmd, env, prev_fd, pipe_fd);
	else if (pid < 0)
		return (perror("fork"), -1);
	*pid_out = pid;
	if (prev_fd != 1)
		safe_close(&prev_fd);
	if (cmd->next)
		safe_close(&pipe_fd[1]);
	if (cmd->next)
		return (pipe_fd[0]);
	return (-1);
}

// Crée un pipe uniquement si la commande suivante existe
int	setup_pipe(int pipe_fd[2], t_command *cmd)
{
	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}

// Ferme les bons descripteurs et met à jour prev_fd dans le proces parent
int	handle_parent_after_fork(pid_t pid, t_command *cmd, int prev_fd,
		int pipe_fd[2])
{
	if (pid == -1)
	{
		perror("fork");
		clean_and_exit(get_shell_context(NULL), EXIT_FAILURE);
	}
	if (prev_fd != -1)
		safe_close(&prev_fd);
	if (cmd->next && pid != 0)
	{
		safe_close(&pipe_fd[1]);
		return (pipe_fd[0]);
	}
	if (!cmd->next)
	{
		if (pipe_fd[0] != -1)
			safe_close(&pipe_fd[0]);
		if (pipe_fd[1] != -1)
			safe_close(&pipe_fd[1]);
	}
	return (-1);
}

// Attend ts les proces enfants et met à jour le code de sortie du shell
void	wait_for_all_children(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->last_exit_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
}
