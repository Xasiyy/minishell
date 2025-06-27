/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:40:04 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/25 17:57:25 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gère l'expansion de $? (code de sortie)
static void	handle_exit_status(char **res, int *i, int exit_code)
{
	char	*exit_status;

	exit_status = ft_itoa(exit_code);
	*res = append_expanded_to_result(*res, exit_status);
	//free(exit_status);
	(*i)++;
}

// quote est inutilisé donc on le marque comme tel
static void	handle_dollar(char *str, int *i, int quote __attribute__((unused)),
		t_shell *sh, char **res)
{
	char	*expanded;

	if (str[*i] == '?')
		handle_exit_status(res, i, sh->last_exit_status);
	else if (!ft_isalpha(str[*i]) && str[*i] != '_')
		*res = append_char_to_result(*res, '$');
	else
	{
		expanded = expand_and_append_var(str, i, sh);
		*res = append_expanded_to_result(*res, expanded);
		free(expanded);
	}
}

// Fait l'expansion des variables dans une chaîne ($VAR, $?)
char	*expand_variables(char *str, int quote_type, t_shell *shell)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && quote_type != 1 && str[i + 1])
		{
			i++;
			handle_dollar(str, &i, quote_type, shell, &res);
		}
		else
			res = append_char_to_result(res, str[i++]);
	}
	return (res);
}
