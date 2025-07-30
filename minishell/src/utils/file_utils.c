/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:57:08 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/30 13:02:00 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_file(const char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	return (fd);
}

int	open_output_file(const char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	return (fd);
}

void	cleanup_and_exit(int fd, int *pipe_fd)
{
	if (fd != -1)
		safe_close(&fd);
	if (pipe_fd)
	{
		safe_close(&pipe_fd[0]);
		safe_close(&pipe_fd[1]);
	}
	exit(1);
}
