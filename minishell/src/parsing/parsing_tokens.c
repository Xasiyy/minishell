/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:25:20 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/23 14:22:50 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_redir_pieces(char *t)
{
	size_t	pieces;
	int		k;
	int		len;

	pieces = 1;
	k = 0;
	len = ft_strlen(t);
	while (k < len)
	{
		if ((t[k] == '<' || t[k] == '>'))
		{
			if (k + 1 < len && t[k + 1] == t[k])
				k += 2;
			else
				k += 1;
			pieces++;
			if (k < len)
				pieces++;
		}
		else
			k++;
	}
	return (pieces);
}

// Extract each word or string btwn quotation marks str and add them to tokens
void	fill_token(const char *str, char **tokens, int *i, int *tok_i)
{
	int		start;
	char	quote;

	while (str[*i])
	{
		while (is_space(str[*i]))
			(*i)++;
		start = *i;
		quote = 0;
		while (str[*i])
		{
			if ((str[*i] == '\'' || str[*i] == '"') && quote == 0)
				quote = str[*i];
			else if (str[*i] == quote)
				quote = 0;
			else if (!quote && is_space(str[*i]))
				break ;
			(*i)++;
		}
		if (*i > start)
			tokens[(*tok_i)++] = ft_substr(str, start, *i - start);
	}
}

char	**split_tokens(const char *str)
{
	char	**tokens;
	int		i;
	int		tok_i;

	i = 0;
	tok_i = 0;
	tokens = malloc(sizeof(char *) * (count_tokens(str) + 1));
	if (!tokens)
		return (NULL);
	fill_token(str, tokens, &i, &tok_i);
	tokens[tok_i] = NULL;
	return (tokens);
}
