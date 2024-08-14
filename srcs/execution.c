/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:47 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 10:10:36 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signal(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	ft_memset(&sa, 0, sizeof(sa));
	set_termios(2);
	sa.sa_handler = sig_ctrl_c;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sb, 0, sizeof(sb));
	sb.sa_handler = heredoc_handler;
	sigaction(SIGQUIT, &sb, NULL);
}

void	do_dups(t_shell *ms)
{
	if (!(ms->read_end == -1))
	{
		close(ms->read_end);
		ms->read_end = -1;
	}
	dup2(ms->fd[0], 0);
	dup2(ms->fd[1], 1);
	close(ms->fd[0]);
	close(ms->fd[1]);
}

int	do_command(t_shell *ms, t_process_node *process)
{
	if (!process->builtin)
		do_dups(ms);
	dprintf(2, "in do cmd process->builtin:%d\n", process->builtin);
	if (process->builtin)
		return (ms->excode = call_builtin (ms, process));
	if (get_path(process, ms))
		return (-1);
	if (process->cmd_path != NULL)
		execve(process->cmd_path, process->command, ms->envp);
	if (access(process->command[0], F_OK) == 0)
	{
		error_msg(process->command[0], 0, "is a directory", ms->excode = 126);
		return (-1);
	}
	error_msg(process->command[0], 0,
		"No such file or directory", ms->excode = 1);
	// ft_putstr_fd(process->command[0], 2);
	// ft_putstr_fd("No such file or directory\n", 2);
	// return (set_exitcode(ms, 1));
	return (-1);
}

int	do_process(t_process_node *process, t_shell *ms)
{

	if (ms->fork_n == 1 && process->builtin)
	{
		if (do_command(ms, process) == -1)
			return (-1);
	}
	else
	{
		ms->pids[ms->count] = fork();
		child_signal();
		if (ms->pids[ms->count] < 0)
		{
			ft_putstr_fd("shell: error: fork failed\n", 2);
			return (set_exitcode(ms, -1));
		}
		if (ms->pids[ms->count] == 0)
		{
			if (do_command(ms, process))
			{
				return (-1);
			}
		}
	}
	return (0);
}
