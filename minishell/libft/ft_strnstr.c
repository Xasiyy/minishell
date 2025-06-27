/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:55:14 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/24 17:55:55 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l;
	size_t	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	l = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			while (little[l] && big[i + l] && \
			(i + l) < len && big[i + l] == little[l])
				l++;
			if (!little[l])
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

/* int main(void)
{
	const char *big = "hey";
	void *little = "";

	char *result = ft_strnstr(big, little, 15);
	if (result)
		printf("Trouvé : %s\n", result);
	else
		printf("NULL\n");

	return 0;
} */
