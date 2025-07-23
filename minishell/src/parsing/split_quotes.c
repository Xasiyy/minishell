/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:28:11 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/23 13:50:42 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reallocate chain table ac larger size
char	**ft_realloc_split(char **old, int new_size)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * new_size);
	if (!new)
		return (NULL);
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = NULL;
	free(old);
	return (new);
}

static char	*extract_redirection_token(const char *input, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	if (input[*i] == input[start])
		(*i)++;
	return (ft_substr(input, start, *i - start));
}

// Extract a token from the string, respecting the quotation marks
char	*extract_token(const char *input, int *i)
{
	int		start;
	char	quote;
	char	*token;

	if (input[*i] == '<' || input[*i] == '>')
		return (extract_redirection_token(input, i));
	start = *i;
	quote = 0;
	while (input[*i])
	{
		if (!quote && (input[*i] == '\'' || input[*i] == '"'))
			quote = input[(*i)++];
		else if (quote && input[*i] == quote)
		{
			(*i)++;
			quote = 0;
		}
		else if (!quote && (is_space(input[*i])
				|| input[*i] == '<' || input[*i] == '>'))
			break ;
		else
			(*i)++;
	}
	token = ft_substr(input, start, *i - start);
	return (token);
}

// Decodes a line into tokens, respecting () single and double
char	**split_respecting_quotes(const char *input)
{
	int		i;
	char	**tokens;
	char	*token;
	int		count;

	i = 0;
	tokens = NULL;
	count = 0;
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		token = extract_token(input, &i);
		tokens = ft_realloc_split(tokens, count + 2);
		if (!tokens)
			return (NULL);
		tokens[count++] = token;
		tokens[count] = NULL;
	}
	return (tokens);
}
