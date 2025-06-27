/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:57:07 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/17 14:19:28 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

// Verif si chaine entier valide sans erreur
int	is_valid_numeric(const char *str)
{
	int	error;

	ft_strtoll(str, &error);
	return (!error);
}

// Verif si prochaine multiplication par 10 + digit cause depassement
static int	check_limits(long long res, int digit, int sign)
{
	if (sign == 1 && res > (LLONG_MAX - digit) / 10)
		return (1);
	if (sign == -1 && res > (-(LLONG_MIN + digit)) / 10)
		return (1);
	return (0);
}

// Initialise indices et signe
static int	init_parse(const char *str, int *i, int *sign)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (str[*i] < '0' || str[*i] > '9')
		return (0);
	return (1);
}

// Convertit en long long et detecte erreur
long long	ft_strtoll(const char *str, int *error)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	*error = 0;
	if (!init_parse(str, &i, &sign))
		return (*error = 1, 0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_limits(res, str[i] - '0', sign))
			return (*error = 1, 0);
		res = res * 10 + (str[i++] - '0');
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (*error = 1, 0);
	return (res * sign);
}

// builtin_exit : Gère la commande exit, avec validation des arguments
void	builtin_exit(char **cmd, t_shell *shell)
{
	pid_t	parent_pid;

	// printf("exit\n");
	parent_pid = get_shell_context(NULL)->main_pid;
	if (getpid() != parent_pid)
	{
		handle_exit_child(cmd, shell);
		return ;
	}
	handle_exit_parent(cmd, shell);
}
