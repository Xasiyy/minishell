/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:47:34 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/30 13:02:08 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_partial_array(char **arr, int i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
}

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
