/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:58:48 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/16 17:00:52 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int character)
{
	if (character != '\0' && character >= 'A' && character <= 'Z')
		character = character + 32;
	return (character);
}

/* int main() {
	char c;

	printf("Entrer un caractère majuscule: ");
	scanf("%c", &c);

	char upper = ft_tolower(c);

	printf("Minuscule de %c est %c\n", c, upper);

	return 0;
} */