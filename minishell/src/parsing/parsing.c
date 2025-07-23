/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:27:50 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 13:54:05 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// manage $ and $?
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

// Adds a character to the end of a string (reallocates)
char	*append_char_to_result(char *result, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(result, ft_strdup(tmp)));
}

// Recovers the variable's value from its name and adds it to the string
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

// Add an expanded string to the final result
char	*append_expanded_to_result(char *result, char *expanded)
{
	if (!expanded)
		return (result);
	return (ft_join_free_both(result, expanded));
}
