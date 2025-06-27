/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:32:45 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/25 12:20:58 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = nmemb * size;
	if (!nmemb || !size || total_size / size != nmemb)
		return (malloc(0));
	ptr = (void *)malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

/* void	*ft_memset(void *dest, int c, size_t count)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)dest;
	while (i < count)
	{
		p[i] = (unsigned int)c;
		i++;
	}
	return (dest);
} */
/* int main ()
{
    size_t nmemb = 5;
    size_t i = 0;
    int *tab = (int *)ft_calloc(nmemb, sizeof(int));

    while (i < nmemb)
    {
        printf("tab[%zu] = %d\n", i, tab[i]);
        i++;
    }
} */
