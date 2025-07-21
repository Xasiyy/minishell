/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:39:47 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/20 16:14:53 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Libere ttes les ressources liees a la structure shell
void	free_all(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->pipeline)
	{
		if (shell->pipeline->commands)
			free_command_list(shell->pipeline->commands);
		free(shell->pipeline);
		shell->pipeline = NULL;
	}
}

// Libere une liste chainee de cmd
void	free_command_list(t_command *cmd_list)
{
	t_command	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		free_command(cmd_list);
		cmd_list = tmp;
	}
}

// Libère la liste chaînée des redirections
void	free_redirections(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

// Libere une structure t_command et ses champs
void	free_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->args && cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->delimiter);
	free(cmd->path);
	free_redirections(cmd->redirections);
	free(cmd);
}

// Libere une structure t_env et son tableau envp
void	free_env(t_env *env)
{
	int	i;

	if (!env)
		return ;
	if (env->envp)
	{
		i = 0;
		while (env->envp[i])
		{
			free(env->envp[i]);
			i++;
		}
		free(env->envp);
	}
	free(env);
}
