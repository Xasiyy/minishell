/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:41:42 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/16 18:09:21 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pr trier ordre alpha variable d env
void	sort_env(char **env)
{
	int		i;
	int		swapped;
	char	*tmp;

	if (!env || !env[0])
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (env[i + 1])
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

// Affiche une ligne de variable dans le format export
static void	print_sorted_line(char *var)
{
	char	*equal_pos;

	equal_pos = ft_strchr(var, '=');
	if (equal_pos)
	{
		*equal_pos = '\0';
		printf("declare -x %s=\"%s\"\n", var, equal_pos + 1);
		*equal_pos = '=';
	}
	else
		printf("declare -x %s\n", var);
}

// Affiche l'environnement trié dans le format export
void	print_sorted_env(char **env)
{
	char	**sorted;
	int		i;

	sorted = copy_env(env);
	if (!sorted)
		return ;
	sort_env(sorted);
	if (!sorted[0])
	{
		free_split(sorted);
		return ;
	}
	i = 0;
	while (sorted[i])
		print_sorted_line(sorted[i++]);
	free_split(sorted);
}
