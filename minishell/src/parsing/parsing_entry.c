/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:54:45 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/02 21:36:28 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parsing(char *input, t_shell *shell)
{
	char		**tokens;
	int			*quote_flags;
	t_command	*cmd;

	tokens = parsing_token_setup(input);
	if (!tokens)
		return (NULL);
	quote_flags = init_quote_flags(tokens);
	if (!quote_flags)
		return (free_split(tokens), NULL);
	cmd = build_command(tokens, quote_flags, shell);
	free_split(tokens);
	free(quote_flags);
	if (!cmd || ((!cmd->args || !cmd->args[0]) && cmd->redirections == NULL))
	{
		if (cmd)
			free_command(cmd);
		return (NULL);
	}
	return (cmd);
}

t_command	*build_command(char **tokens, int *quote_flags, t_shell *shell)
{
	t_command	*cmd;

	expand_all_tokens_with_quotes(tokens, quote_flags, shell);
	discard_empty_words(tokens, quote_flags);
	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	parse_redirections(tokens, quote_flags, cmd);
	return (cmd);
}

// Init un tableau de flags pr indiquer les quotes sur chaque token
int	*init_quote_flags(char **tokens)
{
	int	*flags;
	int	count;
	int	i;

	count = 0;
	while (tokens[count])
		count++;
	flags = ft_calloc(count, sizeof(int));
	if (!flags)
		return (NULL);
	i = 0;
	while (i < count)
		flags[i++] = 0;
	return (flags);
}

// Nettoie, découpe et vérifie les tokens
char	**parsing_token_setup(char *input)
{
	char	*cleaned;
	char	**tokens;

	if (!input || has_unclosed_quotes(input))
		return (NULL);
	cleaned = trim_withespaces(input);
	if (!cleaned)
		return (NULL);
	tokens = split_respecting_quotes(cleaned);
	free(cleaned);
	if (!tokens)
		return (NULL);
	tokens = split_internat_redirs(tokens);
	if (!tokens || syntax_error(tokens))
	{
		free_split(tokens);
		return (NULL);
	}
	return (tokens);
}

// Applique les expansions à chaque token (variables d’environnement.)
void	expand_all_tokens(char **tokens, t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokens[i])
	{
		expanded = parse_and_expand_token(tokens[i], shell);
		free(tokens[i]);
		tokens[i] = expanded;
		i++;
	}
}
