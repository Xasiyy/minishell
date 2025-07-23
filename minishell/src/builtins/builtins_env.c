/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:21:29 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 14:19:56 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Displays the absolute path of the current repeat
int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

// Displays all current env variables
int	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

// Deletes an env variable
int	builtin_unset(char **cmd, t_env *env_struct)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (unset_env_var(&env_struct->envp, cmd[i]) != 0)
		{
			perror("unset");
			return (1);
		}
		i++;
	}
	return (0);
}

// Check if variabable d env already exists
int	env_var_exists(char **env, const char *key)
{
	int		i;
	size_t	len;

	if (!env || !key)
		return (0);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}
