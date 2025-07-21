/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:35:41 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/20 11:52:37 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_tmp_filename(void)
{
	static int	id;
	char		*num_str;
	char		*result;

	num_str = ft_itoa(getpid() + id++);
	if (!num_str)
		return (NULL);
	result = ft_strjoin("/tmp/minishell_heredoc_", num_str);
	free(num_str);
	return (result);
}

int	loop_heredoc(int fd, char *delimiter)
{
	char	*line;

	g_signal = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT_HEREDOC || !line)
		{
			if (line)
				free(line);
			return (1);
		}
		if (ft_strncmp(line, delimiter,
				ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\0')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	create_heredoc_file(char **template_name)
{
	char	*template;
	int		fd;

	template = generate_tmp_filename();
	if (!template)
		return (-1);
	fd = open(template, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(template);
		return (-1);
	}
	*template_name = template;
	return (fd);
}

int	check_signal_hook(void)
{
	if (g_signal == SIGINT_HEREDOC)
	{
		rl_done = 1;
		return (0);
	}
	return (0);
}

char	*handle_heredoc(char *delimiter)
{
	char	*template;
	int		fd;
	int		result;
	void	(*old_sigint)(int);
	void	(*old_sigquit)(int);

	rl_event_hook = check_signal_hook;
	fd = create_heredoc_file(&template);
	if (fd == -1)
		return (NULL);
	old_sigint = signal(SIGINT, heredoc_sigint);
	old_sigquit = signal(SIGQUIT, SIG_IGN);
	result = loop_heredoc(fd, delimiter);
	rl_event_hook = NULL;
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, old_sigquit);
	if (result != 0 || g_signal == SIGINT_HEREDOC)
	{
		if (g_signal == SIGINT_HEREDOC)
			g_signal = SIGINT;
		else
			g_signal = 0;
		return (safe_close(&fd), unlink(template), free(template), NULL);
	}
	return (safe_close(&fd), template);
}
