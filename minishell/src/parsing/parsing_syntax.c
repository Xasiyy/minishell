/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:40:25 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/30 13:24:39 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char *tok)
{
	if (tok && tok[0] == '|' && tok[1] == '\0')
		return (1);
	return (0);
}

void	print_unexpected(char *tok)
{
	if (tok)
		ft_eprintf("minishell: error near unexpected token '%s'\n", tok);
	else
		ft_eprintf("minishell: error near unexpected token 'newline'\n");
}

int	expect_filename(char **t, int *i)
{
	char	*next;

	(*i)++;
	next = t[*i];
	if (!next || is_special(next))
	{
		print_unexpected(next);
		return (1);
	}
	return (0);
}

// Vérifie les erreurs spécifiques aux pipes
static int	check_pipe_block(char **t, int *i)
{
	if (t[*i + 1] && is_pipe(t[*i + 1]))
	{
		print_unexpected(t[*i + 1]);
		return (1);
	}
	(*i)++;
	while (t[*i] && is_redirection(t[*i]))
	{
		if (expect_filename(t, i))
			return (1);
	}
	if (!t[*i] || is_special(t[*i]))
	{
		print_unexpected(t[*i]);
		return (1);
	}
	return (0);
}

// Parcourt tous les tokens et vérifie la syntaxe
int	check_tokens(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if (is_pipe(t[i]))
		{
			if (check_pipe_block(t, &i))
				return (1);
			continue ;
		}
		if (is_redirection(t[i]))
		{
			if (expect_filename(t, &i))
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}
