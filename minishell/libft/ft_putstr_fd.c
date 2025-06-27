/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:21:43 by asdiallo          #+#    #+#             */
/*   Updated: 2025/05/21 16:03:27 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Écrit une chaîne sur le descripteur de fichier donné
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/*void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write (fd, s, 1);
		s++;
	}
}*/

/* int main()
{
	ft_putstr_fd("'Hello", 1);
	return (0);
} */
