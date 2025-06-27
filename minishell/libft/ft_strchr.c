/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:03:29 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/22 12:37:11 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

/* int main() {
	const char *str = "Bonjour, comment ça va ?";
	char ch = 'c';

	// Appel à la fonction strchr
	char *result = ft_strchr(str, ch);

	if (result != NULL) {
		printf("'%c' %ld\n", ch, result - str);
	} else {
		printf("Le caractère '%c' n'a pas été trouvé dans la chaîne.\n", ch);
	}

	return 0;
} */