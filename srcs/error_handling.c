/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:45:25 by alli              #+#    #+#             */
/*   Updated: 2024/07/31 17:33:53 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token, t_shell *ms)//error_occured need to revise only for parsing test
{
	char	c;

	c = *(token + 1);
	if (c == '\'' || c == '\"')
		ft_putstr_fd("shell: unexpected EOF while looking for matching", 2);
	else
		ft_putstr_fd("syntax error near unexpected token", 2);
	ms->excode = 258;
	return (1);
}

void	error_handle(t_shell *ms)
{
	if (!ms->envp)//hsu added for <infile
		return ;
	if (ms->envp)
	{
		ft_free_strs(ms->envp, 0, 0);
		// free(ms);
		if (ms->line)
			free(ms->line);
		exit(ms->excode);
	}
	ft_printf("Readline unable to read");
	exit(ms->excode);
}

void	error_msg(char *cmd, char *str, char *msg)
{
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

void	cmd_not_found(char *str, t_shell *ms)
{
	ft_putstr_fd("Command ", 2);
	ft_putchar_fd(39, 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd(39, 2);
	ft_putstr_fd(" not found\n", 2);
	ms->excode = 127;
}

void	only_print_error(char *name)
{
	if (ft_putstr_fd("lobster-shell 🦞: in only print error", 2) == -1)
	{
		perror("pipex: write error");
		exit(1);
	}
	perror(name);
	exit(1);
}