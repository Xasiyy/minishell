/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:35:41 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/30 21:47:40 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*handle_heredoc(char *delimiter)
{
	char	template[] = "/tmp/minishell_heredocXXXXXX";
	int		fd;
	char	*line;
	int		pid;
	int		status;
	
	//fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd = mkstemp(template);
	if (fd == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
	{
		safe_close(&fd);
		unlink(template);
		return (NULL);
	}
	else if (pid == 0)
	{
		signal(SIGINT, heredoc_sigint);
		signal(SIGQUIT, SIG_IGN);
		while (1)
		{
			line = readline("> ");
			if(!line)
			{
				safe_close(&fd);
				exit (0);
			}
			if (ft_strcmp(line, delimiter) == 0)
			{
				safe_close(&fd);
				_exit(0);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		safe_close(&fd);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, sigint_handler);
		g_signal = 0;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			unlink(template);
			safe_close(&fd);
			return (NULL);
		}
	}
	safe_close(&fd);
	return (ft_strdup(template));
}
