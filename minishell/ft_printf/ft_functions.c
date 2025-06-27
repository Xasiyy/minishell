/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:11:09 by asdiallo          #+#    #+#             */
/*   Updated: 2025/05/15 13:16:33 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write (2, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

void	ft_putnbr_unsigned(unsigned int n)
{
	if (n >= 10)
		ft_putnbr_unsigned(n / 10);
	ft_putchar((n % 10) + '0');
}

void	ft_putnbr_hexa(unsigned int nbr, int upp)
{
	char	*base;

	if (upp)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nbr >= 16)
		ft_putnbr_hexa((nbr / 16), upp);
	ft_putchar(base[nbr % 16]);
}

void	ft_print_p(void *p)
{
	unsigned long	addr;

	addr = (unsigned long)p;
	ft_putstr("0x");
	ft_putnbr_hexa(addr, 0);
}
