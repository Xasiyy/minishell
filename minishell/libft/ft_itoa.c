/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:03:04 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/02 21:31:19 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trouve_len(int len)
{
	int	i;

	i = 0;
	if (len <= 0)
		i++;
	while (len != 0)
	{
		i++;
		len = len / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		len;
	int		s;

	s = 1;
	len = trouve_len(n);
	r = (char *)malloc(len + 1);
	if (!r)
		return (NULL);
	r[len] = '\0';
	if (n == 0)
		r[0] = '0';
	if (n < 0)
	{
		r[0] = '-';
		s = -s;
	}
	while (n != 0)
	{
		r[--len] = (n % 10) * s + '0';
		n = n / 10;
	}
	return (r);
}
