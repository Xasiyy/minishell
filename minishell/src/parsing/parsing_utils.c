/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmailc.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:04:45 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/21 10:06:31 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char *tok)
{
	int	i;

	if (!tok)
		return (0);
	if (tok[0] != '|')
		return (0);
	i = 0;
	while (tok[i] == '|')
		i++;
	if (tok[i] == '\0' && i == 1)
		return (1);
	return (0);
}

// Verifie si espace ou tab
int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

// compte les tokens
int	count_tokens(const char *str)
{
	int		count;
	int		in_token;
	char	quote;

	quote = 0;
	count = 0;
	in_token = 0;
	while (*str)
	{
		update_quote(*str, &quote);
		if (!quote && !is_space(*str))
		{
			if (!in_token)
			{
				count++;
				in_token = 1;
			}
		}
		else if (!quote && is_space(*str))
			in_token = 0;
		str++;
	}
	return (count);
}

// fonction utils pour savoir si un token est un operateur
int	is_special(char *token)
{
	if (!token)
		return (0);
	return (!ft_strncmp(token, "|", 2) || !ft_strncmp(token, "<", 2)
		|| !ft_strncmp(token, ">", 2) || !ft_strncmp(token, ">>", 3)
		|| !ft_strncmp(token, "<<", 3));
}

// fonction utils pour savoir si un token en une redirrection
int	is_redirection(char *token)
{
	if (!token || (token[0] != '<' && token[0] != '>'))
		return (0);
	if (token[0] == '\"' || token[0] == '\'')
		return (0);
	return (1);
}
