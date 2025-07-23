/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:59:25 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 14:13:02 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <sys/stat.h>

// Manages command execution (builtin or external)
void	execute_command(t_command *cmd, char **env, int *exit_status)
{
	int	save_in;
	int	save_out;
	int	ret;

	(void)env;
	if ((!cmd || !cmd->args || !cmd->args[0]
			|| cmd->args[0][0] == '\0') && cmd->redirections)
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		ret = handle_redirections(cmd);
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		safe_close(&save_in);
		safe_close(&save_out);
		*exit_status = (ret == -1);
		return ;
	}
	parent_process(cmd, env, exit_status);
}

// Executes a builtin requiring a fork
void	execute_external_builtin(char **args, char **env, int *exit_status)
{
	pid_t	pid;
	int		status;

	(void)env;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_builtin(args, exit_status);
		exit(*exit_status);
	}
	else if (pid > 0)
		handle_parent_process(pid, &status, exit_status);
	else
	{
		perror("fork");
		*exit_status = 1;
	}
}

void	execute_external(t_command *cmd, char **env, int *exit_status)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (handle_redirections(cmd) == -1)
		{
			free_shell(get_shell_context(NULL), 1);
			exit(1);
		}
		execute_child(cmd, env);
		free_shell(get_shell_context(NULL), 1);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		handle_parent_process(pid, &status, exit_status);
	else
	{
		perror("fork");
		*exit_status = 1;
	}
}

// Manage the parent process after a fork
void	handle_parent_process(pid_t pid, int *status, int *exit_status)
{
	t_shell	*shell;
	int		sig;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, status, 0);
	init_signals();
	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit\n", 2);
		else if (sig == SIGINT)
			ft_putchar_fd('\n', 1);
		*exit_status = 128 + sig;
	}
	else if (WIFEXITED(*status))
		*exit_status = WEXITSTATUS(*status);
	else
		*exit_status = 1;
	shell = get_shell_context(NULL);
	shell->last_exit_status = *exit_status;
}

// Execute each command in the linked list
void	execute_commands(t_command *cmd_list, t_env *env)
{
	int		exit_status;
	t_shell	*shell;

	shell = get_shell_context(NULL);
	exit_status = 0;
	while (cmd_list)
	{
		execute_command(cmd_list, env->envp, &exit_status);
		shell->last_exit_status = exit_status;
		cmd_list = cmd_list->next;
	}
}
