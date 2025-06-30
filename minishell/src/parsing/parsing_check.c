/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:32:43 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/30 13:21:03 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Vérifie si la cmd commence par un token invalide (ex: |)
static int	is_invalid_start(char **tokens)
{
	if (!tokens || !tokens[0])
		return (0);
	if (tokens[0][0] == '|' && tokens[0][1] != '\0')
	{
		ft_eprintf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (ft_strcmp(tokens[0], "|") == 0)
	{
		print_unexpected(tokens[0]);
		return (1);
	}
	return (0);
}

// Vérif si la cmd se termine par un token invalide (ex: |)
static int	is_invalid_end(char **tokens)
{
	int	i;
	int	len;

	i = 0;
	while (tokens[i + 1])
		i++;
	len = ft_strlen(tokens[i]);
	if (len > 0 && tokens[i][len - 1] == '|')
	{
		print_unexpected("|");
		return (1);
	}
	if (ft_strcmp(tokens[i], "|") == 0)
	{
		print_unexpected(tokens[i]);
		return (1);
	}
	return (0);
}

// Vérif la syntaxe pipes redirections
static int	check_pipes_and_redirs(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|\0", 2))
		{
			if ((tokens[i + 1] && !ft_strncmp(tokens[i + 1], "|\0", 2)))
			{
				print_unexpected(tokens[i + 1]);
				return (1);
			}
		}
		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0
			|| ft_strcmp(tokens[i], "<<") == 0 || ft_strcmp(tokens[i],
				">>") == 0)
		{
			if (expect_filename(tokens, &i))
				return (1);
		}
		i++;
	}
	return (0);
}

// Vérif les erreurs de syntaxe dans les tokens
int	syntax_error(char **tokens)
{
	if (is_invalid_start(tokens))
		return (1);
	if (is_invalid_end(tokens))
		return (1);
	if (check_pipes_and_redirs(tokens))
		return (1);
	if (check_tokens(tokens))
		return (1);
	return (0);
}

// Sup les args vides ("") de la liste des argts d'une cmd
void	remove_empty_args(t_command *cmd)
{
	int		i;
	int		j;
	char	**args;

	args = cmd->args;
	i = 0;
	j = 0;
	if (!args)
		return ;
	while (args[i])
	{
		if (args[i][0] != '\0')
			args[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	args[j] = NULL;
}
