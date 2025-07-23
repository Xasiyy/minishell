/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:46:34 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 14:08:53 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, int force_env)
{
	if (!shell)
		return ;
	if ((getpid() == shell->main_pid || force_env) && shell->env)
	{
		if (shell->env)
		{
			free_env(shell->env);
			shell->env = NULL;
		}
	}
	free_all(shell);
	free(shell);
}

void	clean_and_exit(t_shell *shell, int exit_code)
{
	free_shell(shell, 1);
	exit(exit_code);
}

char	*ft_join_free_left(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*ft_join_free_both(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

void	free_segments(t_segment *seg)
{
	t_segment	*tmp;

	while (seg)
	{
		tmp = seg->next;
		free(seg->value);
		free(seg);
		seg = tmp;
	}
}
