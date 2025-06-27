/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:53:46 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/17 15:37:12 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/* int main(void)
{
	char *s = "Hello, World!";
	char *substr;

	// Cas 1 : Sous-chaîne normale
	substr = ft_substr(s, 7, 5);
	printf("Sous-chaîne (start: 7, len: 5): %s\n", substr);
	free(substr);  // Libérer la mémoire allouée

	// Cas 2 : start est plus grand que la longueur de la chaîne
	substr = ft_substr(s, 20, 5);
	printf("Sous-chaîne (start: 20, len: 5): %s\n", substr);
	free(substr);

	// Cas 3 : start est valide,
		mais len est plus grand que la longueur restante
	substr = ft_substr(s, 7, 50);
	printf("Sous-chaîne (start: 7, len: 50): %s\n", substr);
	free(substr);

	// Cas 4 : Sous-chaîne vide avec start à la fin
	substr = ft_substr(s, ft_strlen(s), 5);
	printf("Sous-chaîne (start: fin, len: 5): %s\n", substr);
	free(substr);

	return (0);
} */