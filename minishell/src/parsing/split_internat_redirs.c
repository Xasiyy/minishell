/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_internat_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmailc.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:00:35 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/21 10:29:46 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_quote_state(int quote, char c)
{
	if (!quote && (c == '\'' || c == '"'))
		return (c);
	if (quote && c == quote)
		return (0);
	return (quote);
}

static void	handle_double_redir(char **t, char **out, size_t *j, int k)
{
	if (k > 0)
		out[(*j)++] = ft_substr(*t, 0, k);
	out[(*j)++] = ft_substr(*t, k, 2);
	*t += k + 2;
}

static void	handle_simple_redir(char **t, char **out, size_t *j, int k)
{
	if (k > 0)
		out[(*j)++] = ft_substr(*t, 0, k);
	out[(*j)++] = ft_substr(*t, k, 1);
	*t += k + 1;
}

int	process_redir_token(char **t, char **out, size_t *j, int k)
{
	int	len;

	len = ft_strlen(*t);
	if ((*t)[k] == '>' || (*t)[k] == '<')
	{
		if (k + 1 < len && (*t)[k + 1] == (*t)[k])
		{
			handle_double_redir(t, out, j, k);
			return (1);
		}
		else
		{
			handle_simple_redir(t, out, j, k);
			return (1);
		}
	}
	return (0);
}

char	**split_internat_redirs(char **tokens)
{
	size_t	i;
	size_t	j;
	size_t	total;
	char	**out;

	i = 0;
	total = 0;
	while (tokens[i])
	{
		total += count_redir_pieces(tokens[i]);
		i++;
	}
	out = malloc((total + 1) * sizeof * out);
	if (!out)
		return (tokens);
	i = 0;
	j = 0;
	while (tokens[i])
		split_token_redirs(tokens[i++], out, &j);
	out[j] = NULL;
	free_split(tokens);
	return (out);
}
