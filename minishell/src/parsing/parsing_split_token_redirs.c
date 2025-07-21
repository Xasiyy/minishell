/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_token_redirs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmailc.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:25:45 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/21 10:26:15 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_token_redirs(char *t, char **out, size_t *j)
{
	int	k;
	int	len;
	int	quote;

	k = 0;
	quote = 0;
	len = ft_strlen(t);
	while (k < len)
	{
		quote = update_quote_state(quote, t[k]);
		if (!quote && (t[k] == '>' || t[k] == '<'))
		{
			if (process_redir_token(&t, out, j, k))
			{
				len = ft_strlen(t);
				k = 0;
				continue ;
			}
		}
		k++;
	}
	if (len > 0)
		out[(*j)++] = ft_strdup(t);
}
