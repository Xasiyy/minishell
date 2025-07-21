/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:55:38 by xasiy             #+#    #+#             */
/*   Updated: 2025/07/20 12:07:34 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_env_no_value(const char *key)
{
	char	*new_var;
	size_t	key_len;
	size_t	i;

	key_len = ft_strlen(key);
	new_var = malloc(key_len + 1);
	if (!new_var)
		return (NULL);
	i = 0;
	while (i < key_len)
	{
		new_var[i] = key[i];
		i++;
	}
	new_var[i] = '\0';
	return (new_var);
}

char	*make_env_entry(const char *key, const char *value)
{
	char	*new_var;
	size_t	key_len;
	size_t	val_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	val_len = 0;
	if (value)
		val_len = ft_strlen(value);
	if (!value || val_len == 0)
		return (make_env_no_value(key));
	new_var = malloc(key_len + val_len + 2);
	if (!new_var)
		return (NULL);
	ft_strcpy(new_var, key);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	return (new_var);
}
