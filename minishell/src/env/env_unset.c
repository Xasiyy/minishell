/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:43:36 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/01 16:07:19 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Crée une copie de l'env sans la variable correspondant à la clé donnée
static char	**create_env_without_key(char **env, const char *key)
{
	int		i;
	int		j;
	size_t	key_len;
	int		count;
	char	**new_env;

	i = 0;
	j = 0;
	key_len = ft_strlen(key);
	count = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
			free(env[i++]);
		else
			new_env[j++] = env[i++];
	}
	new_env[j] = NULL;
	return (new_env);
}

// Supprime une variable d'env par sa clé
int	unset_env_var(char ***env, const char *key)
{
	int		i;
	size_t	key_len;
	char	**new_env;

	if (!env || !*env || !key)
		return (1);
	key_len = ft_strlen(key);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, key_len) == 0)
		{
			new_env = create_env_without_key(*env, key);
			if (!new_env)
				return (1);
			free(*env);
			*env = new_env;
			return (0);
		}
		i++;
	}
	return (0);
}
