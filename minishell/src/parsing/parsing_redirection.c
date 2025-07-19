/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:28:04 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/19 21:40:49 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ajoute redirection a la liste chaine des redirection d une cmd
void	add_redirection(t_command *cmd, t_redir_type type, char *filename)
{
	t_redir	*new = malloc(sizeof(*new));
	t_redir	*tmp;
	char	*tmpfile;

	if (!new || !filename)
	{
		ft_eprintf("minishell: internal redirection error (invalid filename)\n");
		return ;
	}
	if (type == REDIR_HEREDOC)
	{
		tmpfile = handle_heredoc(filename);
		free(filename);
		if (!tmpfile)
		{
			free(new);
			ft_eprintf("minishell: heredoc failed\n");
			return;
		}
		new->filename = tmpfile;
	}
	else
	{
		new->filename = ft_strdup(filename);
		free(filename);
	}
	new->type = type;
	new->next = NULL;
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

void	expand_all_tokens_with_quotes(char **tokens, int *quote_flags,
		t_shell *shell)
{
	int			i;
	t_segment	*segments;
	char		*expanded;

	i = 0;
	while (tokens[i])
	{
		segments = split_segments(tokens[i]);
		if (!segments)
		{
			quote_flags[i] = 0;
			i++;
			continue ;
		}
		quote_flags[i] = segments->quote;
		expanded = build_expanded_string(segments, shell);
		free(tokens[i]);
		tokens[i] = expanded;
		free_segments(segments);
		i++;
	}
}

// Détecte le type de redirection et extrait le nom de fichier
void	handle_redirection(char **tokens, int *i, t_command *cmd)
{
	t_redir_type	type;
	char			*filename;
	char			*expanded;
	t_shell			*shell;
	t_redir *redir = cmd->redirections;
	while (redir)
		redir = redir->next;
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
}

// Retourne le type de redirection selon le token
t_redir_type	get_redirection_type(char *t)
{
	if (t[0] == '<' && t[1] == '<')
		return (REDIR_HEREDOC);
	else if (t[0] == '<')
		return (REDIR_IN);
	else if (t[0] == '>' && t[1] == '>')
		return (REDIR_APPEND);
	else if (t[0] == '>')
		return (REDIR_OUT);
	return (-1);
}

// Extrait le nom du fichier pour la redirection
char	*extract_redirection_filename(char **tokens, int *i)
{
	char	*t;

	t = tokens[*i];
	if (!t)
		return (NULL);
	if (t[1] && t[1] != '<' && t[1] != '>')
	{
		return (t + 1);
	}
	if (!tokens[*i + 1])
		return (NULL);	
	*i += 1;
	if (!tokens[*i] || tokens[*i][0] == '\0')
		return (NULL);
	return (tokens[*i]);
}
