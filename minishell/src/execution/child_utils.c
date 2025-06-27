/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:47:47 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/17 15:42:49 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Configure les redirections,duplique les bons descripteurs,
// puis exécute la commande ds le processus fils
void	fork_and_run_child(t_command *cmd, char **env, int prev_fd,
		int pipe_fd[2])
{
	t_shell	*shell;
	int		local_status;

	shell = get_shell_context(NULL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (handle_redirections(cmd) == -1)
	{
		free_shell(shell, 1);
		exit(1);
	}
	local_status = 0;
	execute_command(cmd, env, &local_status);
	free_shell(shell, 1);
	_exit(local_status);
}

// Cree un tube de communication avec vérification d’erreur
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

// Cree un new processus avec fork()
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
