/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:18:15 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/28 17:40:53 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Vérifie si commande fournie est interne Shell
int	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "exit")
		|| !ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "env")
		|| !ft_strcmp(cmd[0], "pwd"))
		return (1);
	return (0);
}

// Exécute un builtin
int	execute_builtin(char **cmd, int *exit_status)
{
	t_shell	*shell;

	shell = get_shell_context(NULL);
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "cd") == 0)
		*exit_status = builtin_cd(cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		*exit_status = builtin_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		*exit_status = builtin_pwd();
	else if (ft_strcmp(cmd[0], "env") == 0)
		*exit_status = builtin_env(shell->env->envp);
	else if (ft_strcmp(cmd[0], "export") == 0)
		*exit_status = builtin_export(cmd, shell->env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		*exit_status = builtin_unset(cmd, shell->env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		builtin_exit(cmd, shell);
	else
		return (0);
	return (1);
}

// Execute un builtin ac redirection en sauvardant/restorant les fd
int	execute_builtin_redirection(t_command *cmd, int *exit_status)
{
	int	stdout_backup;
	int	stdin_backup;

	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	if (stdout_backup < 0 || stdin_backup < 0)
	{
		perror("dup");
		return (1);
	}
	if (handle_redirections(cmd) == -1)
	{
		*exit_status = 1;
		dup2(stdout_backup, STDOUT_FILENO);
		dup2(stdin_backup, STDIN_FILENO);
		safe_close(&stdout_backup);
		safe_close(&stdin_backup);
		return (1);
	}
	execute_builtin(cmd->args, exit_status);
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	safe_close(&stdout_backup);
	safe_close(&stdin_backup);
	return (0);
}

// Verifie si l option -n passe a echo est valide
int	is_valid_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// Construit une liste chainee de cmd a partir d un tableau
t_command	*build_cmd_list(t_command **cmds)
{
	t_command	*head;
	t_command	*last;

	head = NULL;
	last = NULL;
	while (*cmds)
	{
		if (!head)
		{
			head = *cmds;
			last = head;
		}
		else
		{
			last->next = *cmds;
			last = last->next;
		}
		cmds++;
	}
	if (last)
		last->next = NULL;
	return (head);
}
