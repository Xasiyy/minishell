/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncullu <ncullu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:46:34 by ncullu            #+#    #+#             */
/*   Updated: 2025/06/17 16:46:32 by ncullu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Libere tt memoire alloue pr structure principale shell
void	free_shell(t_shell *shell, int force_env)
{
	if (!shell)
		return ;
	if ((getpid() == shell->main_pid || force_env) && shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
	free_all(shell);
	free(shell);
}

// Libère la mémoire et quitte le programme ac le code donné
void	clean_and_exit(t_shell *shell, int exit_code)
{
	free_shell(shell, 1);
	exit(exit_code);
}

// Ne libère que la première chaîne
char	*ft_join_free_left(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

// Libère les deux chaînes (s1 et s2 doivent toutes deux venir du heap)
char	*ft_join_free_both(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

// Libere une liste chainee de segments
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
