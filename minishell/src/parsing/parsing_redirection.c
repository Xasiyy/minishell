/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:28:04 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/23 14:00:33 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	validate_redirection_params(t_redir_type type,
			char *expanded, int *i)
{
	if ((int)type == -1)
		return (0);
	if (!expanded || expanded[0] == '\0')
	{
		ft_eprintf("minishell: syntax error near unexpected token 'newline'\n");
		free(expanded);
		(*i)++;
		return (0);
	}
	return (1);
}

// Detects the type of redirection and extracts the file name
void	handle_redirection(char **tokens, int *i, t_command *cmd)
{
	t_redir_type	type;
	char			*filename;
	char			*expanded;
	t_shell			*shell;

	shell = get_shell_context(NULL);
	type = get_redirection_type(tokens[*i]);
	filename = extract_redirection_filename(tokens, i);
	if (!filename)
	{
		ft_eprintf("minishell: syntax error near unexpected token `newline'\n");
		(*i)++;
		return ;
	}
	expanded = expand_variables(filename, QUOTE_NONE, shell);
	free(filename);
	if (!validate_redirection_params(type, expanded, i))
		return ;
	add_redirection(cmd, type, expanded);
	(*i)++;
}

// Returns the type of redirection according to the token
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

// Extract file name for redirection
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
