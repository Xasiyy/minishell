/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:33:22 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/02 21:29:14 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int searchedChar)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i > 0)
	{
		if (str[i] == (char)searchedChar)
			return ((char *)&str[i]);
		i--;
	}
	if (str[0] == (char)searchedChar)
		return ((char *)&str[0]);
	if (searchedChar == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
