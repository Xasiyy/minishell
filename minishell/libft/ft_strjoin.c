/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:52:26 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/19 14:15:15 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(s1 || s2))
		return (NULL);
	str = (char *)malloc(len1 + len2 + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcat(str, s2, len1 + len2 + 1);
	return (str);
}

/* int main(void)
{
	char *s1 = "Hello, ";
	char *s2 = "World!";
	char *result;

	// Cas 1 : Cas normal
	result = ft_strjoin(s1, s2);
	printf("Resultat (s1 + s2): %s\n", result);
	free(result); // Libérer la mémoire allouée

	// Cas 2 : s1 est vide
	result = ft_strjoin("", s2);
	printf("Resultat (s1 vide + s2): %s\n", result);
	free(result);

	// Cas 3 : s2 est vide
	result = ft_strjoin(s1, "");
	printf("Resultat (s1 + s2 vide): %s\n", result);
	free(result);

	// Cas 4 : Les deux chaînes sont vides
	result = ft_strjoin("", "");
	printf("Resultat (s1 vide + s2 vide): %s\n", result);
	free(result);

	return 0;
} */