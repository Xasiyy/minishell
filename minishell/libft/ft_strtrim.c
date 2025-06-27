/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:48:55 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/22 13:52:21 by asdiallo         ###   ########.fr       */
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

/* int main()
{
	char *s1= "lorem \n ipsum \t dolor \n sit \t amet";
	char *set = " ";
	char *r = ft_strtrim(s1, set);

	printf("'%s'\n", r);
	free(r);
	return (0);
} */