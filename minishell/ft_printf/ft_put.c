/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:50:44 by asdiallo          #+#    #+#             */
/*   Updated: 2025/05/15 13:16:24 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	ft_putchar(char c)
{
	write (2, &c, 1);
}

void	ft_putstr(char *s)
{
	if (!s)
	{
		write (2, "(null)", 6);
		return ;
	}
	while (*s)
	{
		write (2, s, 1);
		s++;
	}
}
