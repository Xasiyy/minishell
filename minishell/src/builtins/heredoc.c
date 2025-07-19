/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:35:41 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/20 01:27:26 by xasiy            ###   ########.fr       */
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

/* char	*generate_tmp_filename(void)
{
	char	*base = "/tmp/minishell_heredoc_";
	char	*filename;
	char	num[12];
	int		pid = getpid();
	static	int	counter = 0;
	int		i = 0, j = 0;

	while (pid > 0)
	{
		num[i++] = (pid % 10) + '0';
		pid /= 10;
	}
	num[i] = 0;
	filename = malloc(ft_strlen(base) + i + 6 + 1);
	if (!filename)
		return (NULL);
	while (base[j])
	{
		filename[j] = base[j];
		j++;
	}
	while (--i >= 0)
		filename[j++] = num[i];
	filename[j++] = '_';
	filename[j++] = (counter / 100) % 10 + '0';
	filename[j++] = (counter / 10) % 10 + '0';
	filename[j++] = (counter % 10) + '0';
	counter++;

	filename[j] = '\0';
	return (filename);
} */

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

int check_signal_hook(void)
{
    if (g_signal == SIGINT_HEREDOC)
    {
        rl_done = 1;
        return 0;
    }
    return 0;
}

char	*handle_heredoc(char *delimiter)
{
	char	*template;
	int		fd;
	void(*old_sigint)(int);
	void(*old_sigquit)(int);
	int result;

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
		safe_close(&fd);
		unlink(template);
		free(template);
		return (NULL);
	}
	safe_close(&fd);
	return (template);
}
