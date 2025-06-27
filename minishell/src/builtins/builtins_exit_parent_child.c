/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit_parent_child.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:06:10 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/17 14:18:08 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verif si cmd "exit" trp args
int	is_too_many_args(char **cmd, t_shell *shell)
{
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	return (0);
}

// Verif si arg est nbr valide, sinn Q shell
void	check_numeric_exit(char *arg, t_shell *shell, long long *exit_code)
{
	int	error;

	if (!is_valid_numeric(arg))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_and_exit(shell, 2);
	}
	*exit_code = ft_strtoll(arg, &error);
	if (error)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_and_exit(shell, 2);
	}
}

// Gere comportement cmd "exit" ds shell principale
void	handle_exit_parent(char **cmd, t_shell *shell)
{
	long long	exit_code;

	if (!cmd[1])
		clean_and_exit(shell, shell->last_exit_status);
	if (is_too_many_args(cmd, shell))
		return ;
	check_numeric_exit(cmd[1], shell, &exit_code);
	clean_and_exit(shell, (unsigned char)exit_code);
}

// Gere cmd "exit" ds enfant
void	handle_exit_child(char **cmd, t_shell *shell)
{
	long long	code;

	if (!cmd || !cmd[0])
		clean_and_exit(shell, shell->last_exit_status);
	if (!cmd[1])
		clean_and_exit(shell, shell->last_exit_status);
	if (is_too_many_args(cmd, shell))
		clean_and_exit(shell, 1);
	check_numeric_exit(cmd[1], shell, &code);
	clean_and_exit(shell, (unsigned char)code);
}
