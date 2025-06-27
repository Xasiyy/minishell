/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:23:34 by ncullu            #+#    #+#             */
/*   Updated: 2025/05/21 13:36:34 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ajoute ou affiche variable d env ac export
int	builtin_export(char **cmd, t_env *env_struct)
{
	if (!cmd[1])
	{
		print_sorted_env(env_struct->envp);
		return (0);
	}
	return (export_process_args(cmd, env_struct));
}

// Traite chaque argument passé à export
int	export_process_args(char **cmd, t_env *env_struct)
{
	char	*equal;
	int		i;
	int		err;

	i = 1;
	err = 0;
	while (cmd[i])
	{
		equal = ft_strchr(cmd[i], '=');
		if (!is_valid_identifier(cmd[i]))
		{
			write(2, "export: not a valid identifier\n", 31);
			err = 1;
		}
		else if (equal && equal != cmd[i])
			err = handle_export_with_value(env_struct, cmd[i], equal);
		else if (!equal && !env_var_exists(env_struct->envp, cmd[i]))
			add_env_entry(&env_struct->envp, cmd[i], "");
		i++;
	}
	return (err);
}

// Gere le cas ou valeur est incluse ds export VAR=value
int	handle_export_with_value(t_env *env_struct, char *arg, char *equal)
{
	char	*key;
	char	*value;
	int		status;

	key = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	if (!key || !value)
	{
		if (key)
			free(key);
		if (value)
			free(value);
		perror("malloc");
		return (1);
	}
	status = set_env_var(&env_struct->envp, key, value);
	if (status != 0)
		perror("export");
	free(key);
	free(value);
	return (status != 0);
}

// Vérifie si la cle d une variable d env est valide
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
