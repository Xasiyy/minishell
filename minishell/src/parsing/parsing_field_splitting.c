/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_field_splitting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:29:05 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/23 14:03:27 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check whether an empty word can be ignored (unquoted)
static int	is_discradable(char *word, int quote_flag)
{
	return (quote_flag == QUOTE_NONE && word[0] == '\0');
}

// Sup empty unquoted words in tokens and adjust quotes
void	discard_empty_words(char **tok, int *quote)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tok[i])
	{
		if (!is_discradable(tok[i], quote[i]))
		{
			tok[j] = tok[i];
			quote[j] = quote[i];
			j++;
		}
		else
			free(tok[i]);
		i++;
	}
	tok[j] = NULL;
}
