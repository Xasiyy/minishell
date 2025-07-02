/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:48:55 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/02 21:29:11 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*mal;
	size_t		len;

	start = s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = ft_strlen(s1) + s1;
	while (end > start && ft_strchr(set, *(end - 1)))
		end--;
	len = end - start;
	mal = (char *)malloc(len + 1);
	if (mal == NULL)
		return (NULL);
	ft_strlcpy(mal, start, len + 1);
	mal[len] = '\0';
	return (mal);
}
