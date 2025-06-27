/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:55:45 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/24 10:41:37 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Applique toutes les redirections définies sur la commande
/* void	handle_redirection(char **tokens, int *i, t_command *cmd)
{
	t_redir_type	type;
	char			*filename;
	char			*expanded;
	t_shell			*shell;
	t_redir *redir = cmd->redirections;
	while (redir)
	{
		fprintf(stderr, "[debug] redir type = %d, filename ptr = %p, val = %s\n",
			redir->type, (void *)redir->filename,
			redir->filename ? redir->filename : "NULL");
		redir = redir->next;
	}
	shell = get_shell_context(NULL); 
	type = get_redirection_type(tokens[*i]);
	if ((int)type == -1)
		return ;
	filename = extract_redirection_filename(tokens, i);
	if (!filename)
	{
		ft_eprintf("minishell: syntax error near unexpected token `newline'\n");
		(*i)++;
		return ;
	}
	expanded = expand_variables(filename, QUOTE_NONE, shell);
	free(filename);
	if (!expanded || expanded[0] == '\0')
	{
		ft_eprintf("minishell: syntax error near unexpected token 'newline'\n");
		free(expanded);
		(*i)++;
		return ;
	}
	add_redirection(cmd, type, expanded);
	(*i)++;
} */
