/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_internat_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:00:35 by ncullu            #+#    #+#             */
/*   Updated: 2025/05/27 16:11:54 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
static int	update_quote_state(int quote, char c)
{
	if (!quote && (c == '\'' || c == '"'))
		return (c);
	if (quote && c == quote)
		return (0);
	return (quote);
}

//
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

#include "minishell.h"

static int	process_redir_token(char **t, char **out, size_t *j, int k)
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
	out = malloc((total + 1) * sizeof *out);
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
