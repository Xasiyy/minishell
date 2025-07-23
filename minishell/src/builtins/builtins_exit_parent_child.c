/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit_parent_child.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:06:10 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 14:19:19 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// Check if arg is nbr valid, sinn Q shell
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

// Gere behavior cmd “exit” ds main shell
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

// Gere cmd “exit” ds child
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
