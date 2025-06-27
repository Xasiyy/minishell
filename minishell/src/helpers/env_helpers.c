/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:12:09 by ncullu            #+#    #+#             */
/*   Updated: 2025/05/21 16:14:11 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Recupere la valeur d une variable d environnemement
char	*get_env_value(char **env, const char *var)
{
	size_t	len;
	int		i;

	if (!env || !var)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '='
			&& (env[i][len + 1] || env[i][len + 1] == '\0'))
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

// récupère la variable d'enviro PATH à partir de liste variables d'enviro
char	*find_path_in_env(char **env)
{
	if (!env)
		return (NULL);
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

// Affiche erreur
void	ft_error(char *msg)
{
	perror(msg);
	exit(1);
}
