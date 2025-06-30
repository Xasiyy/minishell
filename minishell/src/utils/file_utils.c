/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:57:08 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/28 17:42:45 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ouvre un fichier en lecture et return son descripteur
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

// Ouvre\cree un fichier en ecriture ac 0644
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

// Ferme descripteur de fichier et termine programme
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
