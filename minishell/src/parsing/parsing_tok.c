/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:27:49 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 13:57:10 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cut out a token and expand it according to the quotes
char	*parse_and_expand_token(const char *token, t_shell *shell)
{
	t_segment	*segments;
	char		*result;

	segments = split_segments(token);
	if (!segments)
		return (ft_strdup(token));
	result = build_expanded_string(segments, shell);
	free_segments(segments);
	return (result);
}

// Traverses the segments and builds the final expanded string
char	*build_expanded_string(t_segment *segments, t_shell *shell)
{
	t_segment	*curr;
	char		*result;
	char		*expanded;

	curr = segments;
	result = NULL;
	while (curr)
	{
		if (curr->quote == QUOTE_SIMPLE)
			expanded = ft_strdup(curr->value);
		else if (curr->quote == QUOTE_DOUBLE)
			expanded = expand_variables(curr->value, 2, shell);
		else
			expanded = expand_variables(curr->value, 0, shell);
		if (!result)
			result = expanded;
		else
			result = ft_join_free_both(result, expanded);
		curr = curr->next;
	}
	return (result);
}
