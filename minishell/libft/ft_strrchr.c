/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:33:22 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/19 11:21:51 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int searchedChar)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i > 0)
	{
		if (str[i] == (char)searchedChar)
			return ((char *)&str[i]);
		i--;
	}
	if (str[0] == (char)searchedChar)
		return ((char *)&str[0]);
	if (searchedChar == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

/* int main() {
	const char *str = "bonjour";
	char ch = 'b';

	char *result = ft_strrchr(str, ch);

	if (result != NULL) 
		printf(" '%c' trouvé à la position : %ld\n", ch, result - str);
	 else
		printf("Le caractère '%c' n'a pas été trouvé dans la chaîne.\n", ch);
	return 0;
} */