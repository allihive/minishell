/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:58:20 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 15:11:35 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_children(t_shell *ms, int *pids, int count)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < count - 1)
	{
		if (pids[i] == -1)
		{
			i++;
			continue ;
		}
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			ms->excode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms->excode = WTERMSIG(status) + 128;
		if (ms->excode == 131)
			ft_putstr_fd("^\\Quit: 3\n", 2);
		else if (ms->excode == 130)
			ft_putstr_fd("^C\n", 2);
		i++;
	}
	return (ms->excode);
}

int	check_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			return (1);
		i++;
	}
	return (0);
}

int	pipex(t_process_node *process, t_shell *ms)
{
	while (ms->count < ms->fork_n)
	{
		while (ifisspace(*process->node_line))
			(process->node_line)++;
		if (get_fd(process->node_line, process, ms) == -1)
			return (close_and_free(ms));
		if (do_process(process, ms) == -1)
			return (close_and_free(ms));
		if (ms->pids[ms->count] == 0)
			return (close_and_free(ms));
		close(ms->fd[0]);
		close(ms->fd[1]);
		ms->count++;
		if (process->next)
			process = process->next;
	}
	wait_children(ms, ms->pids, (ms->fork_n + 1));
	return (ms->excode);
}
