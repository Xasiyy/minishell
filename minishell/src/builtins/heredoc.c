/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:35:41 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/19 21:57:13 by xasiy            ###   ########.fr       */
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

	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			ft_eprintf("heredoc delimited by end of the file (wanted `EOF')\n");
			return (1);
		}
		if (ft_strncmp(line, delimiter,
				ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
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

int	execute_heredoc_child(int fd, char *delimiter, char *template)
{
	int	pid;
	int	status;
	int	ret;

	pid = fork();
	if (pid == -1)
	{
		safe_close(&fd);
		unlink(template);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sigint);
		signal(SIGQUIT, SIG_IGN);
		ret = loop_heredoc(fd, delimiter);
		safe_close(&fd);
		exit(ret);
	}
	safe_close(&fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	return (status);
}

char	*handle_heredoc(char *delimiter)
{
	char	*template;
	int		fd;
	int		status;
	char	*result;

	fd = create_heredoc_file(&template);
	if (fd == -1)
		return (NULL);
	status = execute_heredoc_child(fd, delimiter, template);
	if (status == -1)
		return (unlink(template), free(template), NULL);
	g_signal = 0;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signal = SIGINT;
		unlink(template);
		free(template);
		return (NULL);
	}
	result = ft_strdup(template);
	free(template);
	return (result);
}
