/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:28 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 15:07:24 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exitcode(t_shell *ms, int exitcode)
{
	ms->excode = exitcode;
	return (-1);
}

int	first_child(char *input, t_process_node *process, t_shell *ms)
{
	close(ms->fd[0]);
	close(ms->fd[1]);
	if (pipe(ms->fd) == -1)
	{
		ft_putstr_fd("shell: error opening a pipe\n", 2);
		return (set_exitcode(ms, -1));
	}
	ms->read_end = dup(ms->fd[0]);
	close(ms->fd[0]);
	return (go_check_redirect(input, process, ms));
}

int	middle_child(char *input, t_process_node *process, t_shell *ms)
{
	int	tmp_fd;

	if (pipe(ms->fd) == -1)
	{
		ft_putstr_fd("shell: error opening a pipe\n", 2);
		return (set_exitcode(ms, -1));
	}
	tmp_fd = dup(ms->read_end);
	dup2(ms->fd[0], ms->read_end);
	dup2(tmp_fd, ms->fd[0]);
	close(tmp_fd);
	return (go_check_redirect(input, process, ms));
}

int	last_child(char *input, t_process_node *process, t_shell *ms)
{
	dup2(ms->read_end, ms->fd[0]);
	close(ms->read_end);
	ms->fd[1] = dup(1);
	return (go_check_redirect(input, process, ms));
}

int	get_fd(char *input, t_process_node *process, t_shell *ms)
{
	if (ms->fork_n == 1)
		return (go_check_redirect(input, process, ms));
	if (ms->count == 0)
		return (first_child(input, process, ms));
	else if (ms->count == ms->fork_n -1)
		return (last_child(input, process, ms));
	else
		return (middle_child(input, process, ms));
	return (0);
}
