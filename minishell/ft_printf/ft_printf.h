/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:45:06 by asdiallo          #+#    #+#             */
/*   Updated: 2025/05/15 14:42:32 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

/* typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list; */
void	ft_putchar(char c);
void	ft_putstr(char *s);
int		ft_eprintf(const char *format, ...);
void	ft_putnbr(int n);
void	ft_putnbr_hexa(unsigned int nbr, int upp);
void	ft_print_p(void *p);
void	ft_putnbr_unsigned(unsigned int n);
int		handle_format(const char **format, va_list arg);

#endif