/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:55:41 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/03 15:48:48 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reste_readline(void)
{
	rl_reset_line_state();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Boucle principale du shell : lit et exécute les commandes
void	start_shell_loop(t_shell *shell)
{
	char	*line;
	char	**tmp;

	while (1)
	{
		//signal(SIGINT, sigint_handler);
		setup_interactive_signals();
		line = readline("minishell$ ");
		if (!line && g_signal == SIGINT)
		{
			shell->last_exit_status = 130;
			g_signal = 0;
			continue ;
		}
		if (!line)
		{
			printf("exit\n");
			free_shell(shell, 0);
			exit(0);
		}
		tmp = split_respecting_quotes(line);
		if (tmp && syntax_error(tmp))
		{
			free_split(tmp);
			free(line);
			shell->last_exit_status = 2;
			continue ;
		}
		free_split(tmp);
		handle_line(line, shell);
		free_all(shell);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	ft_bzero(shell, sizeof(t_shell));
	if (!shell)
		return (1);
	get_shell_context(shell);
	shell->env = init_env(envp);
	shell->pipeline = NULL;
	init_signals();
	shell->main_pid = getpid();
	//setup_interactive_signals();
	start_shell_loop(shell);
	free_shell(shell, 1);
	return (0);
}
