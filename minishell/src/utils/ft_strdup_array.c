/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:47:34 by asdiallo          #+#    #+#             */
/*   Updated: 2025/05/21 16:20:11 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Libère un tableau partiellement alloué (jusqu'à l'index i)
static void	free_partial_array(char **arr, int i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
}

// Duplique un tableau de chaînes de caractères
char	**ft_strdup_array(char **src)
{
	int		i;
	int		size;
	char	**copy;

	if (!src)
		return (NULL);
	size = 0;
	while (src[size])
		size++;
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
		{
			free_partial_array(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
