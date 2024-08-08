/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:45:25 by alli              #+#    #+#             */
/*   Updated: 2024/08/08 14:30:06 by yhsu             ###   ########.fr       */
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
		ft_putstr_fd("syntax error near unexpected token\n", 2);
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
	// ft_printf("Readline unable to read");
	exit(ms->excode);
}

void	error_msg(char *cmd, char *str, char *msg, int excode, t_shell *ms)
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
	ms->excode = excode; //changed the args to add exit code
}

void	heredoc_input_msg(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
	global_signal = 0;
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
	if (ft_putstr_fd("minishel: in only print error", 2) == -1)
	{
		perror("pipex: write error");
		exit(1);
	}
	perror(name);
	exit(1);
	close_and_free(ms);
}