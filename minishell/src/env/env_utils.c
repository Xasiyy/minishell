/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:12:12 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/30 11:03:05 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Make a complete copy of the existing env array
char	**copy_env(char **envp)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// Add an env variable
int	add_env_entry(char ***env, const char *key, const char *value)
{
	int		count;
	char	**new_env;
	char	*new_var;

	count = 0;
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	if (copy_old_env(new_env, *env, count))
		return (1);
	new_var = make_env_entry(key, value);
	if (!new_var)
	{
		free(new_env);
		return (1);
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free_split(*env);
	*env = new_env;
	return (0);
}

// Copy the former array into a new one
int	copy_old_env(char **new_env, char **old_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (1);
		}
		i++;
	}
	return (0);
}

// Update the env variable or add it if inexistant
int	set_env_var(char ***env, const char *key, const char *value)
{
	int		i;
	size_t	key_len;
	char	*new_var;

	if (!key || !value || !*env)
		return (1);
	key_len = ft_strlen(key);
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, key_len))
		{
			free((*env)[i]);
			new_var = make_env_entry(key, value);
			if (!new_var)
				return (1);
			(*env)[i] = new_var;
			return (0);
		}
		i++;
	}
	return (add_env_entry(env, key, value));
}
