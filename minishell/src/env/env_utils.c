/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:12:12 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/20 12:05:21 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fait une copie complète du tableau d'env existant
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

// Ajoute une variable d'environnement key=value à l'env
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

// Copie l'ancien tableau env dans le nouveau
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

// Met à jour une variable d'env ou l'ajoute si elle n'existe pas
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
		if (ft_strncmp((*env)[i], key, key_len) == 0
			&& (*env)[i][key_len] == '=')
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
