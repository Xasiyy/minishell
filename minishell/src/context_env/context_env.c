/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:01:11 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 14:15:18 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// To store or retrieve the global shell context
t_shell	*get_shell_context(t_shell *set_shell)
{
	static t_shell	*ctx = NULL;

	if (set_shell != NULL)
		ctx = set_shell;
	return (ctx);
}

// Find the shell pointer from an env and t_shell field
t_shell	*get_shell_from_env(t_env *env)
{
	static t_shell	*shell_ptr = NULL;

	if (env == NULL)
		return (shell_ptr);
	shell_ptr = (t_shell *)((char *)env - offsetof(t_shell, env));
	return (shell_ptr);
}

// Count the number of strings in an array of strings (e.g. envp)
static int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// Copy environment variables into a t_env structure
t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	int		count;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	count = count_env(envp);
	env->envp = malloc(sizeof(char *) * (count + 1));
	if (!env->envp)
		return (free_env(env), NULL);
	i = 0;
	while (envp[i])
	{
		env->envp[i] = ft_strdup(envp[i]);
		if (!env->envp[i])
			return (free_env(env), NULL);
		i++;
	}
	env->envp[i] = NULL;
	return (env);
}
