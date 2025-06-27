/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:52:46 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/23 13:51:46 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int search, size_t size)
{
	size_t				i;
	const unsigned char	*p;
	unsigned char		c;

	i = 0;
	c = (unsigned char)search;
	p = (const unsigned char *)ptr;
	while (i < size)
	{
		if (*p == c)
			return ((void *)p);
		i++;
		p++;
	}
	return (NULL);
}
