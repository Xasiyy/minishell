/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:34:19 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/02 21:31:54 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Écrit une chaîne suivie "\n" sur le descripteur de fichier donné
void	ft_putendl_fd(char *s, int fd)
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
	write(fd, "\n", 1);
}
