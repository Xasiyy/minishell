/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:31:22 by asdiallo          #+#    #+#             */
/*   Updated: 2025/05/23 15:19:55 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	handle_char(const char **format, va_list arg)
{
	if (**format == 'c')
		ft_putchar(va_arg(arg, int));
	else if (**format == 's')
	{
		ft_putstr(va_arg(arg, char *));
	}
	else if (**format == 'p')
		ft_print_p(va_arg(arg, void *));
	else if (**format == 'd' || **format == 'i')
		ft_putnbr(va_arg(arg, int));
	else if (**format == 'u')
		ft_putnbr_unsigned(va_arg(arg, unsigned int));
	else if (**format == 'x')
		ft_putnbr_hexa(va_arg(arg, unsigned int), 0);
	else if (**format == 'X')
		ft_putnbr_hexa(va_arg(arg, unsigned int), 1);
	else if (**format == '%')
		ft_putchar('%');
	else
		return (0);
	(*format)++;
	return (1);
}

int	handle_format(const char **format, va_list arg)
{
	int	len;

	len = handle_char(format, arg);
	if (len == 0)
	{
		ft_putchar('%');
		ft_putchar(**format);
		len += 2;
	}
	return (len);
}
