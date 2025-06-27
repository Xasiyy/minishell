/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:44:46 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/04 16:43:49 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_len(const char **format, int len )
{
	int	total_len;

	total_len = 0;
	if (len == 0)
	{
		ft_putchar('%');
		ft_putchar(**format);
		total_len += 2;
		(*format)++;
	}
	else
		total_len += len;
	return (total_len);
}

int	ft_eprintf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		total_len;

	va_start(args, format);
	len = 0;
	total_len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			len = handle_format(&format, args);
			total_len += handle_len (&format, len);
		}
		else
		{
			ft_putchar(*format);
			total_len++;
			format++;
		}
	}
	va_end(args);
	return (total_len);
}
