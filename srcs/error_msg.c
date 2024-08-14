/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:45:25 by alli              #+#    #+#             */
/*   Updated: 2024/08/14 12:04:03 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token, t_shell *ms)
{
	char	c;

	c = *(token + 1);
	if (c == '\'' || c == '\"')
		ft_putstr_fd(" shell: unexpected EOF while looking for matching\n", 2);
	else
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		ms->excode = 2;
	}
	return (1);
}

void	error_msg(char *cmd, char *str, char *msg, int excode)
{
	(void)excode;
	if (!ft_strncmp(cmd, "export", 6))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		if (str)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
}

void	heredoc_input_msg(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
	g_global_signal = 0;
}

void	cmd_not_found(char *str, t_shell *ms)
{
	ft_putstr_fd("Command ", 2);
	ft_putchar_fd(39, 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd(39, 2);
	ft_putstr_fd(" not found\n", 2);
	ms->excode = 127;
}

void	print_error_and_free(char *name, t_shell *ms)
{
	if (ft_putstr_fd("minishell: in only print error", 2) == -1)
	{
		ft_putstr_fd("pipex: write error", 2);
		exit(1);
	}
	ft_putstr_fd(name, 2);
	exit(1);
	close_and_free(ms);
}
