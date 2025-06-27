/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:51:30 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/16 17:06:03 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)ptr1;
	p2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < size)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

/* int main() {
	char str1[] = "abcdef";
	char str2[] = "abcdez";
	
	int result = ft_memcmp(str1, str2, 6);
	
	if (result == 0)
		printf("Les chaînes sont égales.\n");
	else if (result < 0)
		printf("str1 est inférieur à str2.\n");
	else
		printf("str1 est supérieur à str2.\n");
	
	return 0;
} */