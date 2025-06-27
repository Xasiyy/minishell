/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:37:10 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/17 20:39:12 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t count)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)dest;
	while (i < count)
	{
		p[i] = 0;
		i++;
	}
}
