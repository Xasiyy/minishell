/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmailc.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:55:05 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/21 11:21:18 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_heredoc_creation(char *filename)
{
	char	*tmpfile;

	tmpfile = handle_heredoc(filename);
	free(filename);
	if (!tmpfile && g_signal != SIGINT_HEREDOC && g_signal != SIGINT)
		ft_eprintf("heredoc delimiter by end of the file (wanted `EOF')\n");
	return (tmpfile);
}

static t_redir	*create_redirection(t_redir_type type, char *filename)
{
	t_redir	*new;
	char	*tmpfile;

	new = ft_calloc(1, sizeof(*new));
	if (!new || !filename)
		return (NULL);
	new->type = type;
	new->next = NULL;
	if (type == REDIR_HEREDOC)
	{
		tmpfile = handle_heredoc_creation(filename);
		if (!tmpfile)
		{
			free(new);
			return (NULL);
		}
		new->filename = tmpfile;
	}
	else
	{
		new->filename = ft_strdup(filename);
		free(filename);
	}
	return (new);
}

static void	append_redirection(t_command *cmd, t_redir *new)
{
	t_redir	*tmp;

	if (!cmd->redirections)
		cmd->redirections = new;
	else
	{
		tmp = cmd->redirections;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_redirection(t_command *cmd, t_redir_type type, char *filename)
{
	t_redir	*new;

	if (!filename)
	{
		ft_eprintf("minishell: redirection error (invalid filename)\n");
		return ;
	}
	new = create_redirection(type, filename);
	if (!new)
		return ;
	append_redirection(cmd, new);
}
