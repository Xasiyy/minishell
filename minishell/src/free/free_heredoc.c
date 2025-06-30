/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:25:00 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/30 21:33:24 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc_child(char *line, int fd, char *template)
{
	if (line)
		free(line);
	safe_close(&fd);
	if (template)
		unlink(template);
}
