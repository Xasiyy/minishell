/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:51:42 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/02 21:35:26 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Traite une ligne lue : parsing + exécution
void	handle_line(char *line, t_shell *shell)
{
	if (!handle_quotes_and_history(line, shell))
		return ;
	shell->pipeline = parse_pipeline(line, shell);
	signal(SIGINT, SIG_IGN);
	execute_pipeline_or_single(shell);
	if (shell->pipeline)
	{
		free_command_list(shell->pipeline->commands);
		free(shell->pipeline);
		shell->pipeline = NULL;
	}
}

// Vérifie les quotes et ajoute à l’historique
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

// Exécute un pipeline si plusieurs commandes, sinon exécute une seule
void	execute_pipeline_or_single(t_shell *shell)
{
	if (!shell->pipeline || !shell->pipeline->commands)
		return ;
	if (shell->pipeline->count > 1)
		execute_pipeline(shell->pipeline, shell->env->envp);
	else
		execute_commands(shell->pipeline->commands, shell->env);
}
