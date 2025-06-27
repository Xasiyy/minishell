/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_field_splitting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:29:05 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/17 16:24:19 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Vérif si un mot vide peut être ignoré (non quoté)
static int	is_discradable(char *word, int quote_flag)
{
	return (quote_flag == QUOTE_NONE && word[0] == '\0');
}

// Sup les mots vides non quotés ds les tokens et ajuste les quotes
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
