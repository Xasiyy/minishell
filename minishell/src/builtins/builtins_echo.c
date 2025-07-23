/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:25:51 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 14:20:08 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Display args, ac or without line feed (-n)
int	builtin_echo(char **cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd[i] && is_valid_n_option(cmd[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
