/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:37:35 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/22 14:20:43 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	fill_buffer(int fd, char *buffer, char **result)
{
	ssize_t	bytes_read;

	if (buffer[0] == '\0')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*result);
			*result = NULL;
			return (-1);
		}
		if (bytes_read == 0)
			return (0);
		buffer[bytes_read] = '\0';
	}
	return (1);
}

char	*extract_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = (char *)malloc(i + 2);
	else
		line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	replace_buffer(buffer);
	return (line);
}

char	*my_free(char *result, char *line)
{
	char	*temp;

	temp = ft_strjoin(result, line);
	free(result);
	free(line);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*read_line(int fd, char *buffer, char *result)
{
	ssize_t	bytes_read;
	char	*line;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = fill_buffer(fd, buffer, &result);
		if (bytes_read <= 0)
			return (result);
		line = extract_line(buffer);
		if (!line)
			return (free(result), NULL);
		if (!result)
			result = line;
		else
		{
			result = my_free(result, line);
			if (!result)
				return (NULL);
		}
		if (ft_strchr(result, '\n'))
			break ;
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = NULL;
	result = read_line(fd, buffer[fd], result);
	return (result);
}
