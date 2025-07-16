/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:19:44 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/16 17:08:56 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		g_signal = 1;
		exit_status(1, 0);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
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

void	handle_heredoc_sigint(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	exit(130);
}
