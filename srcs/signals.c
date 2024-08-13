/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:50:02 by alli              #+#    #+#             */
/*   Updated: 2024/08/13 18:08:53 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		write (1, "\n", 1);
		close (STDIN_FILENO);
		g_global_signal = 2;
	}
}

void	heredoc_init(void)
{
	struct sigaction	sa;
	struct sigaction	sq;

	ft_bzero(&sa, sizeof(sa));
	ft_bzero(&sq, sizeof(sq));
	sa.sa_handler = heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
	sq.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sq, NULL);
}

void	sig_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_global_signal = sig;
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_termios(int mode)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (mode == 2)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_signal(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	ft_memset(&sa, 0, sizeof(sa));
	set_termios(2);
	sa.sa_handler = sig_ctrl_c;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sb, 0, sizeof(sb));
	sb.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sb, NULL);
}
