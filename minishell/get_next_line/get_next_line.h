/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:34:05 by asdiallo          #+#    #+#             */
/*   Updated: 2024/11/15 17:00:09 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char		*ft_strchr(const char *str, int c);
char		*get_next_line(int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		*extract_line(char *buffer);
void		replace_buffer(char *buffer);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
ssize_t		fill_buffer(int fd, char *buffer, char **result);

#endif