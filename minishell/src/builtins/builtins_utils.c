/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:05:27 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/22 14:10:09 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint(int signo)
{
	(void)signo;
	g_signal = SIGINT_HEREDOC;
	rl_done = 1;
}

// Vérifie si une cmd peut être exécutée ds parent (pas de pipe ni redirec)
int	is_safe_in_parent(t_command *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->has_pipe)
		return (0);
	if (cmd->infile || cmd->outfile || cmd->append || cmd->heredoc)
		return (0);
	return (1);
}

// Vérifie si un builtin pt être exécuté ds le parent (cd, echo, pwd, etc.)
int	is_safe_in_executed_parent(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	return (0);
}
