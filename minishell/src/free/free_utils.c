/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:39:47 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 17:24:33 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_redirections(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

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
