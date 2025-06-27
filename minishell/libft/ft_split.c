/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:28:45 by asdiallo          #+#    #+#             */
/*   Updated: 2025/04/09 13:40:31 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_word(char str, char c)
{
	if (!(str == c || str == '\t' || str == '\n'))
		return (0);
	else
		return (1);
}

size_t	count_word(const char *str, char c)
{
	size_t	cont;
	size_t	i;

	i = 0;
	cont = 0;
	while (str[i])
	{
		while (str[i] && find_word(str[i], c))
			i++;
		if (str[i])
		{
			cont++;
			while (str[i] && !find_word(str[i], c))
				i++;
		}
	}
	return (cont);
}

char	*malloc_w(const char *str, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (str[len] && !find_word(str[len], c))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, len + 1);
	return (word);
}

char	**free_split_libft(char **r, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(r[i]);
		i++;
	}
	free(r);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**r;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	r = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!r)
		return (NULL);
	while (s[i])
	{
		while (s[i] && find_word(s[i], c))
			i++;
		if (s[i])
		{
			r[j++] = malloc_w(s + i, c);
			if (!r[j - 1])
				return (free_split_libft(r, j - 1));
			while (s[i] && !find_word(s[i], c))
				i++;
		}
	}
	r[j] = NULL;
	return (r);
}

/* int main ()
{
	char *str = "hello world";
	char **split = ft_split(str, ' ');
	size_t i = 0;
	while (split[i] != NULL)
	{
		printf("%zu , %s\n", i, split[i]);
		i++;
	}
	free(split);
} */