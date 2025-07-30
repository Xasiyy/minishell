/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:51:42 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/30 13:00:28 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free_command_list(pipeline->commands);
	free(pipeline);
}

void	handle_line(char *line, t_shell *shell)
{
	if (!handle_quotes_and_history(line, shell))
		return ;
	g_signal = 0;
	shell->pipeline = parse_pipeline(line, shell);
	if (g_signal == SIGINT)
	{
		shell->last_exit_status = 130;
		if (shell->pipeline)
		{
			free_command_list(shell->pipeline->commands);
			free(shell->pipeline);
		}
		shell->pipeline = NULL;
		return ;
	}
	signal(SIGINT, SIG_IGN);
	execute_pipeline_or_single(shell);
	free_pipeline(shell->pipeline);
	shell->pipeline = NULL;
}

// Check quotes and add to history
int	handle_quotes_and_history(char *line, t_shell *shell)
{
	if (!line)
		return (0);
	if (has_unclosed_quotes(line))
	{
		ft_eprintf("minishell: syntax error: unclosed quote\n");
		shell->last_exit_status = 2;
		return (0);
	}
	add_history(line);
	return (1);
}

// Executes a pipeline if several commands, otherwise executes a single command
void	execute_pipeline_or_single(t_shell *shell)
{
	if (!shell->pipeline || !shell->pipeline->commands)
		return ;
	if (handle_redirections(shell->pipeline->commands) == -1)
	{
		shell->last_exit_status = 1;
		return ;
	}
	if (shell->pipeline->count > 1)
		execute_pipeline(shell->pipeline, shell->env->envp);
	else
		execute_commands(shell->pipeline->commands, shell->env);
}
