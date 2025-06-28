/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:35:41 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/28 17:41:01 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_heredoc(char *delimiter)
{
	char	template[] = "/tmp/minishell_heredocXXXXXX";
	int		fd = mkstemp(template);
	char	*line;

	//fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if(!line)
		{
			ft_eprintf("minishell: heredoc delimited by end-of-file (wanted `EOF')\n");
			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	safe_close(&fd);
	return (ft_strdup(template));
}
