/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:44:07 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/30 12:45:32 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Compte combien partie une ligne contien separe par | ignore pipe entre ()

int	count_pipeline_parts(const char *str)
{
	int		count;
	int		i;
	char	quote;

	count = 1;
	i = 0;
	quote = 0;
	while (str[i])
	{
		update_quote(str[i], &quote);
		if (quote == 0)
		{
			if (str[i] == '|')
				count++;
		}
		i++;
	}
	return (count);
}

// Met a jour l etat ouverture/fermeture () simple ou double
void	update_quote(char c, char *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}

// Extrait portion de str en atnt que partie du pipeline et met a jour indice
int	handle_pipe_split(const char *str, char **parts, t_pipe_state *st)
{
	parts[st->part_i++] = ft_substr(str, st->start, st->i - st->start);
	st->i++;
	while (str[st->i] == ' ')
		st->i++;
	st->start = st->i;
	return (1);
}

// Decoupe ligne cmd en sous partie separe par | en respectant quotes
char	**split_pipeline_tokens(const char *str)
{
	char			**parts;
	char			quote;
	t_pipe_state	st;

	st.i = 0;
	st.part_i = 0;
	st.start = 0;
	quote = 0;
	parts = malloc(sizeof(char *) * (count_pipeline_parts(str) + 1));
	if (!parts)
		return (NULL);
	while (str[st.i])
	{
		update_quote(str[st.i], &quote);
		if (quote == 0)
		{
			if (str[st.i] == '|' || (str[st.i] == '&' && str[st.i + 1] == '&'))
			{
				if (str[st.i] == '&')
					st.i++;
				if (handle_pipe_split(str, parts, &st))
					continue ;
			}
		}
		st.i++;
	}
	parts[st.part_i++] = ft_substr(str, st.start, st.i - st.start);
	parts[st.part_i] = NULL;
	return (parts);
}
