/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:41:46 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/16 17:44:19 by asdiallo         ###   ########.fr       */
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

/* int main ()
{
    int n = 3; 
    char s1[] = "ABC";
    char s2[] = "AB";
    ft_strncmp(s1, s2, n);
    printf("%d", ft_strncmp(s1, s2, n));
} */