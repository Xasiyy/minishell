/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:41:46 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/02 21:32:43 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	int				r;

	r = 0;
	i = 0;
	while (n > i)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			r = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (r);
		}
		if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
