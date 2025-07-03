/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:59:00 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/03 15:28:20 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Variable globale pr signaler une interruption
volatile sig_atomic_t	g_signal = 0;

void sigint_interactive(int signo)
{
    (void)signo;
    g_signal = SIGINT;
    write(1, "^C\n", 3);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	setup_interactive_signals(void)
{
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	struct sigaction sa = {0};
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	g_signal = 0;
}

// Fonction appelee quand utilisateur envoie Ctrl+C (SIGINT)
void	sigint_handler(int signo)
{
	//t_shell *shell;

	//shell = get_shell_context(NULL);
	(void)signo;
	g_signal = SIGINT;
	write(1, "^C\n", 3);
	//shell->last_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sigint(int signo)
{
	(void)signo;
//	g_signal = SIGINT;
	write(1, "\n", 1);
	exit(130);
}

// Handler pr SIGQUIT (Ctrl+\)
void	sigqquit_handler(int signo)
{
	(void)signo;
	g_signal = 2;
}

// Initialise le comportement du shell face aux signaux
void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// Mini gestionnaire de signal pr Ctrl-C
/* void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
} */
