/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:40:25 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/23 13:59:40 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!t)
		return (1);
	(*i)++;
	next = t[*i];
	if (!next)
	{
		if (!t[*i + 1])
		{
			if (ft_strcmp(t[*i - 1], "<<") == 0)
				return (0);
		}
		print_unexpected(NULL);
		return (1);
	}
	if (is_special(next) && ft_strcmp(t[*i - 1], "<<") != 0)
	{
		print_unexpected(next);
		return (1);
	}
	return (0);
}

// Checks for pipe-specific errors
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
		if (!t[*i + 1])
		{
			if (ft_strcmp(t[*i], "<<") == 0)
				break ;
			print_unexpected(NULL);
			return (1);
		}
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

static int	handle_pipe_token(char **t, int *i)
{
	if (is_pipe(t[*i]))
	{
		if (t[*i + 1] == NULL)
			return (print_unexpected(t[*i]), 1);
		if (check_pipe_block(t, i))
			return (1);
		return (0);
	}
	(*i)++;
	if (is_redirection(t[*i]))
	{
		if (expect_filename(t, i))
			return (1);
		return (0);
	}
	return (0);
}

// Scan all tokens and check syntax
int	check_tokens(char **t)
{
	int	i;

	if (is_pipe(t[0]))
		return (print_unexpected(t[0]), 1);
	i = 0;
	while (t[++i])
	{
		if (t[i][0] == '\0')
			return (print_unexpected(""), 1);
		if (is_pipe(t[i]))
		{
			if (handle_pipe_token(t, &i))
				return (1);
			continue ;
		}
	}
	return (0);
}
