/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:06:11 by alli              #+#    #+#             */
/*   Updated: 2024/05/28 13:54:52 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	sig_ctrl_c(int sig)
{
	void(sig);
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	set_signal(int sig)
{
	struct sigaction sa;
	struct sigaction sb;
	
	ft_bzero(&sa, sizeof(sa));
	set_termios(sig);
	sa.sa_handler = sig_ctrl_c;
	sigaction(SIGINT, &sa, NULL);
	ft_bzero(&sb, sizeof(sb)); /*ctrl-\*/
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sb, NULL); 
}
