/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmailc.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:27:50 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/16 14:23:24 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gerer les $ et $?
char	*get_var_name(const char *str, int *i)
{
	int		start;
	char	*name;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	return (name);
}

// Ajoute un caractere a la fin d une chaine (realloue)
char	*append_char_to_result(char *result, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(result, ft_strdup(tmp)));
}

// Recupere valur de la variable a partir de son nom et ajoute a la chaine
char	*expand_and_append_var(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(str, i);
	if (!var_name)
		return (NULL);
	if (!ft_strncmp(var_name, "?", 2))
	{
		free(var_name);
		return (ft_itoa(shell->last_exit_status));
	}
	var_value = get_env_value(shell->env->envp, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_calloc(1, 1));
}

// Ajoute une chaine expande au resultat final
char	*append_expanded_to_result(char *result, char *expanded)
{
	if (!expanded)
		return (result);
	return (ft_join_free_both(result, expanded));
}
