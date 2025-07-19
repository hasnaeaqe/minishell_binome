/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:19:44 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/19 20:26:13 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		exit_status(1, 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
	else
		g_signal = 0;
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}
static void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		exit_status(1, 1);
		write(1, "\n", 1);
		reset_terminal_mode();
		exit(1);
	}
}

void	handle_heredoc_signals(void)
{
	signal(SIGINT, heredoc_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_terminal_mode(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= (ECHOCTL | ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
