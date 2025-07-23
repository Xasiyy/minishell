/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:59:00 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/23 13:48:57 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Global variable to signal an interruption
volatile sig_atomic_t	g_signal = 0;

void	sigint_interactive(int signo)
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
	struct sigaction	sa;

	sa = (struct sigaction){0};
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
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

// Function called when user sends Ctrl+C (SIGINT)
void	sigint_handler(int signo)
{
	(void)signo;
	g_signal = SIGINT_NORMAL;
	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Handler for SIGQUIT (Ctrl+\)
void	sigqquit_handler(int signo)
{
	(void)signo;
	g_signal = 2;
}

// Initialize shell behavior in response to signals
void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
