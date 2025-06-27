/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:12:39 by ncullu            #+#    #+#             */
/*   Updated: 2025/05/21 16:15:08 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cherche commande ds PATH
char	*find_command_in_path(char *cmd, char **env)
{
	if (!cmd || !*cmd || !env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_access(cmd));
	return (find_command_in_env_path(cmd, env));
}

// Verifie si commande est executable
char	*check_access(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

// Cherche comm ds les variable d environnement
char	*find_command_in_env_path(char *cmd, char **env)
{
	char	*path_var;
	char	**path_dirs;
	char	*full_path;
	int		i;

	path_var = get_env_value(env, "PATH");
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	full_path = NULL;
	i = 0;
	while (path_dirs[i])
	{
		full_path = try_path(path_dirs[i], cmd);
		if (full_path)
			break ;
		i++;
	}
	free_split(path_dirs);
	return (full_path);
}

// Teste un chemin possible pr une commande
char	*try_path(char *cmd_path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(cmd_path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

// Vérifie si chemin donné direct exécutable et return une copie chemin si cas
char	*handle_direct_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
