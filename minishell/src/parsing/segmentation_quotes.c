/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segmentation_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmailc.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:43:54 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/21 10:22:59 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cree new segment av une valeur et un type de quote
t_segment	*new_segment(char *value, t_quote_type quote)
{
	t_segment	*seg;

	seg = malloc(sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->value = value;
	seg->quote = quote;
	seg->next = NULL;
	return (seg);
}

// Ajoute un segment a la fin dune liste chainee de segment
void	append_segment(t_segment **list, t_segment *new_seg)
{
	t_segment	*tmp;

	if (!*list)
	{
		*list = new_seg;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_seg;
}

// Gere un segment entre guillemet (simple ou double) puis ajoute liste
void	handle_segment_quote(const char *input, int *i,
		t_segment **segments)
{
	int		start;
	char	*substr;
	int		type;

	if (input[*i] == '\'')
		type = QUOTE_SIMPLE;
	else
		type = QUOTE_DOUBLE;
	start = ++(*i);
	while (input[*i] && input[*i] != input[start - 1])
		(*i)++;
	substr = ft_substr(input, start, *i - start);
	append_segment(segments, new_segment(substr, type));
	if (input[*i] == input[start - 1])
		(*i)++;
}

static void	handle_quouted_segment(const char *input, int *i,
				t_segment **segments)
{
	int		start;
	char	*substr;
	char	quote_type;

	quote_type = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	substr = ft_substr(input, start, *i - start);
	if (quote_type == '\'')
		append_segment(segments, new_segment(substr, QUOTE_SIMPLE));
	else
		append_segment(segments, new_segment(substr, QUOTE_DOUBLE));
	if (input[*i])
		(*i)++;
}

// Decoupe chaine en segment selon les guillemets (simple double ou aucun)
t_segment	*split_segments(const char *input)
{
	t_segment	*segments;
	int			i;
	int			start;
	char		*substr;

	segments = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			handle_quouted_segment(input, &i, &segments);
		else
		{
			start = i;
			while (input[i] && input[i] != '\'' && input[i] != '"')
				i++;
			substr = ft_substr(input, start, i - start);
			append_segment(&segments, new_segment(substr, QUOTE_NONE));
		}
	}
	return (segments);
}
