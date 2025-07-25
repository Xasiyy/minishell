/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:55:41 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/26 00:13:27 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_readline(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	handle_syntax_errors(char **tmp, char *line, t_shell *shell)
{
	if (tmp && syntax_error(tmp))
	{
		free_split(tmp);
		free(line);
		shell->last_exit_status = 2;
		return (1);
	}
	return (0);
}

void	start_shell_loop(t_shell *shell)
{
	char		*line;
	char		**tmp;

	while (1)
	{
		setup_interactive_signals();
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			free_shell(shell, 0);
			exit(0);
		}
		tmp = split_respecting_quotes(line);
		if (handle_syntax_errors(tmp, line, shell))
			continue ;
		if (tmp)
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
	start_shell_loop(shell);
	printf("free_shell main\n");
	free_shell(shell, 1);
	return (0);
}
