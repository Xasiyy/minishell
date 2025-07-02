/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:55:14 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/02 21:32:46 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l;
	size_t	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	l = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			while (little[l] && big[i + l] && \
			(i + l) < len && big[i + l] == little[l])
				l++;
			if (!little[l])
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
