/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:04:32 by ncullu            #+#    #+#             */
/*   Updated: 2025/05/21 16:05:10 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Découpe une chaîne 'str' en tokens selon les délimiteurs 'delim'
char	*ft_strtok(char *str, const char *delim)
{
	static char	*saved;
	char		*token;

	if (str)
		saved = str;
	if (!saved || *saved == '\0')
		return (NULL);
	token = saved;
	while (*saved && !ft_strchr(delim, *saved))
		saved++;
	if (*saved)
		*saved++ = '\0';
	return (token);
}
