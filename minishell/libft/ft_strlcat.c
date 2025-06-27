/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:36:22 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/25 18:07:25 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	i = 0;
	len_dest = 0;
	len_src = 0;
	while (dest[len_dest] != '\0')
		len_dest++;
	while (src[len_src] != '\0')
		len_src++;
	if (len_dest >= size)
		return (size + len_src);
	if (size != 0)
	{
		while (i < len_src && (len_dest + i + 1) < size)
		{
			dest[len_dest + i] = src[i];
			i++;
		}
		dest[len_dest + i] = '\0';
	}
	return (len_dest + len_src);
}

/* int main ()
{
	char dest[14] = "a";
	const char *src = " lorem ipsum dolor sit amet";
	size_t size = 15; 
	ft_strlcat(dest, src, size);
	printf("%s\n", dest);
} */