/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:02:55 by asdiallo          #+#    #+#             */
/*   Updated: 2025/05/23 15:18:42 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// supprime les espaces en debut et fin de chaines
char	*trim_withespaces(const char *str)
{
	char	*end;
	char	*cleaned;

	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	end = (char *)str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;
	cleaned = malloc(end - str + 2);
	if (!cleaned)
		return (NULL);
	ft_strlcpy(cleaned, str, end - str + 2);
	return (cleaned);
}

// verifie si les quotes sont bien fermees
int	has_unclosed_quotes(const char *str)
{
	char	quotes;

	quotes = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && quotes == 0)
			quotes = *str;
		else if (*str == quotes)
			quotes = 0;
		str++;
	}
	return (quotes != 0);
}
