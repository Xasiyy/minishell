/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:31:50 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/19 21:59:12 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gere et change reppertoire cd et met a jour PWD/OLDPWD
int	builtin_cd(char **cmd)
{
	t_shell	*shell;
	char	*target;

	shell = get_shell_context(NULL);
	if (cmd[1] && cmd[2])
		return (ft_putendl_fd("cd: too many arguments", 2), 1);
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		target = getenv("HOME");
		if (!target)
			return (ft_putendl_fd("cd: HOME not set", 2), 1);
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		target = getenv("OLDPWD");
		if (!target)
			return (ft_putendl_fd("cd : OLDPWD not set", 2), 1);
		ft_putendl_fd(target, 1);
	}
	else
		target = cmd[1];
	return (execute_cd(target, shell));
}

// Change repertoire ac chdir et met a jour variable d env
int	execute_cd(char *target, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!target || target[0] == '\0')
	{
		return (0);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (old_pwd && new_pwd)
	{
		set_env_var(&(shell->env->envp), "OLDPWD", old_pwd);
		set_env_var(&(shell->env->envp), "PWD", new_pwd);
	}
	free(old_pwd);
	free(new_pwd);
	return (0);
}
