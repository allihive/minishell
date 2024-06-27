/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:50:02 by alli              #+#    #+#             */
/*   Updated: 2024/06/19 09:01:59 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0; //global variable

void	set_termios(int mode)
{
	struct termios	term;
	
	tcgetattr(STDIN_FILENO, &term);
	if (mode != 2)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void	sig_ctrl_c(int sig)
{
	g_signal = sig;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal(void)
{
	struct sigaction sa;
	struct sigaction sb;
	
	ft_bzero(&sa, sizeof(sa));
	set_termios(2);
	sa.sa_handler = sig_ctrl_c;
	sigaction(SIGINT, &sa, NULL);
	ft_bzero(&sb, sizeof(sb)); /*ctrl-\*/
	sb.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sb, NULL); 

	// have a different heredoc signal checker? 
}