/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:39:13 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/02 21:36:41 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Remplit un tableau de cmd, a partir des partie separe d un pipeline
static void	fill_commands(t_command **cmds, char **parts, t_shell *shell)
{
	int		i;
	int		has_pipe;
	char	*trimmed;

	i = 0;
	has_pipe = (parts[1] != NULL);
	while (parts[i])
	{
		trimmed = trim_withespaces(parts[i]);
		if (!trimmed)
			return ;
		cmds[i] = parsing(trimmed, shell);
		free(trimmed);
		if (cmds[i])
			cmds[i]->has_pipe = has_pipe;
		i++;
	}
	cmds[i] = NULL;
}


// Analyse une ligne cmd contenant un pipeline et construit structure
t_pipeline	*parse_pipeline(char *input, t_shell *shell)
{
	t_pipeline	*pipeline;
	t_command	**cmds;
	char		**parts;
	int			i;
	int			nb_parts;

	parts = split_pipeline_tokens(input);
	if (!parts)
	{
		return (NULL);
	}
	if (check_tokens(parts))
	{
		free_split(parts);
		return (NULL);
	}
	nb_parts = count_pipeline_parts(input);
	cmds = malloc(sizeof(t_command *) * (nb_parts + 1));
	if (!cmds)
		return (free_split(parts), NULL);
	fill_commands(cmds, parts, shell);
	i = 0;
	while (cmds[i])
		i++;
	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (free_split(parts), free(cmds), NULL);
	pipeline->commands = build_cmd_list(cmds);
	pipeline->count = i;
	free_split(parts);
	free(cmds);
	return (pipeline);
}

// Alloue une structure pipeline à partir des cmd parsées
t_pipeline	*allocate_pipeline(char **parts, t_command **cmds)
{
	t_pipeline	*pipeline;
	int			i;

	i = 0;
	while (cmds[i])
		i++;
	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
	{
		while (--i >= 0)
			free_command(cmds[i]);
		free(cmds);
		free_split(parts);
		return (NULL);
	}
	pipeline->commands = build_cmd_list(cmds);
	pipeline->count = i;
	while (--i >= 0)
		free(cmds);
	free_split(parts);
	return (pipeline);
}
