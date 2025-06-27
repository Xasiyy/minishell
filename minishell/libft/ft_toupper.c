/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:35:59 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/16 17:00:43 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int character)
{
	if (character != '\0' && character >= 'a' && character <= 'z')
		character = character - 32;
	return (character);
}

/* int main() {
	char c;

	printf("Entrer un caractère minuscule: ");
	scanf("%c", &c);

	char upper = ft_toupper(c);

	printf("Majuscule de %c est %c\n", c, upper);

	return 0;
} */