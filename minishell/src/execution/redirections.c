/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:28:25 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 21:38:13 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_perror(char *filename)
{
	perror(filename);
	exit(EXIT_FAILURE);
}

int	get_fd_from_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redir->type == REDIR_HEREDOC)
		fd = open(redir->filename, O_RDONLY);
	else
		fd = -1;
	return (fd);
}

int	handle_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirections;
	while (redir)
	{
		fd = get_fd_from_redir(redir);
		if (fd == -1)
		{
			ft_eprintf("minishell: %s: %s\n", redir->filename, strerror(errno));
			return (-1);
		}
		if ((redir->type == REDIR_IN
				|| redir->type == REDIR_HEREDOC)
			&& dup2(fd, STDIN_FILENO) == -1)
			return (safe_close(&fd), -1);
		if ((redir->type == REDIR_OUT
				|| redir->type == REDIR_APPEND)
			&& dup2(fd, STDOUT_FILENO) == -1)
			return (safe_close(&fd), -1);
		safe_close(&fd);
		redir = redir->next;
	}
	return (0);
}
