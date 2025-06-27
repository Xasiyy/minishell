/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:44:12 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/25 17:23:50 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Vérifie si une chaîne est entourée de guillemets simples ou doubles
int	is_quoted(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (len < 2)
		return (0);
	return ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '"' && s[len
				- 1] == '"'));
}

// Compte les arguments non-redirections (utile pour allouer cmd->args)
static int	count_args(char **tok, int *flags)
{
	int	i;
	int	count;
	(void)flags;

	i = 0;
	count = 0;
	while (tok[i])
	{
		if (is_redirection(tok[i]))
		{
			if (tok[i + 1])
				i += 2;
			else
				i += 1;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

// Gère une redirection et l’ajoute à la commande
static int	handle_redir(char **tok, int *i, t_command *cmd)
{
	char	*filename;
	char	*raw = tok[*i];
	int		op_len = 0;

	if (raw[0] == '>' && raw[1] == '>')
		op_len = 2;
	else if (raw[0] == '<' && raw[1] == '<')
		op_len = 2;
	else if (raw[0] == '>' || raw[0] == '<')
		op_len = 1;
	else
		return (syntax_error(&raw), 1);
	if (raw[op_len] != '\0')
		filename = ft_strdup(raw + op_len);
	else
	{
		if (!tok[*i + 1] || is_redirection(tok[*i + 1]))
		{
			syntax_error(&tok[*i + 1]);
			return (1);
		}
		filename = ft_strdup(tok[*i + 1]);
		(*i)++;
	}
	if (!filename)
		return (1);
	add_redirection(cmd, get_redirection_type(raw), filename);
	(*i)++;
	return (0);
}

// Remplit cmd->args avec les arguments restants hors redirections
static int	fill_args(char **tok, int *flags, t_command *cmd)
{
	int	i;
	int	ac;
	(void)flags;

	i = 0;
	ac = 0;
	while (tok[i])
	{
		if (is_redirection(tok[i]))
		{
			if (handle_redir(tok, &i, cmd))
				return (1);
			continue;
		}
		cmd->args[ac++] = ft_strdup(tok[i]);
		i++;
	}
	cmd->args[ac] = NULL;
	return (0);
}

// Parse les redirections et arguments dans les tokens pour remplir cmd
void	parse_redirections(char **tok, int *flags, t_command *cmd)
{
	int	count;

	count = count_args(tok, flags);
	cmd->args = ft_calloc(count + 1, sizeof(char *));
	if (!cmd->args)
		return ;
	if (fill_args(tok, flags, cmd))
		return ;
}

