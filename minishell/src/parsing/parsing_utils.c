/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:04:45 by asdiallo          #+#    #+#             */
/*   Updated: 2025/05/27 13:40:44 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
