/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:28 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 11:32:37 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	set_exitcode(t_shell *ms, int exitcode)
{
	ms->excode = exitcode;
	return (-1);
}

int first_child(char *input, t_process_node *process, t_shell *ms)
{
    close (ms->fd[0]);
	close (ms->fd[1]);
	dprintf(2, "in 1 child aftet close ms->fd[0]%d\n", ms->fd[0]); 
	if (pipe(ms->fd)== -1)
    {
        ft_putstr_fd( "shell: error opening a pipe\n", 2);
		return (set_exitcode(ms, -1));
    }
    ms->read_end = dup(ms->fd[0]);

    //if (ms->fd[0] >= 0)
		close(ms->fd[0]);
	//ms->fd[0] = -1;

	
    return (go_check_redirect(input, process, ms));    
}

int middle_child(char *input, t_process_node *process, t_shell *ms)
{
    int tmp_fd;
    if (pipe(ms->fd)== -1)
    {
        ft_putstr_fd("shell: error opening a pipe\n", 2);
		return (set_exitcode(ms, -1));
    }
    tmp_fd = dup(ms->read_end);
	dprintf(2, "in 2 child ms->read_end%d\n", ms->read_end); 
    dup2(ms->fd[0], ms->read_end);
    dup2( tmp_fd, ms->fd[0]);// use fd[0] to open the file which opened by tmp_fd 
    dprintf(2, "in 2 child ms->read_end%d\n", ms->read_end); 
	dprintf(2, "in 2 child ms->fd[0]%d\n", ms->fd[0]); 
	close(tmp_fd);

    return (go_check_redirect(input, process, ms));
}

int last_child(char *input,t_process_node *process, t_shell *ms)
{
    
	dup2(ms->read_end, ms->fd[0]);
    //if (ms->read_end >= 0)
		close(ms->read_end);
	//ms->read_end = -1;
    ms->fd[1] = dup(1);
	dprintf(2, "in last child ms->fd[1]%d\n", ms->fd[1]); 
	
    return (go_check_redirect(input, process, ms));
}

int get_fd(char *input, t_process_node *process, t_shell *ms)
{
    if (ms->fork_n == 1)//command == 1
    { 
		return (go_check_redirect(input, process, ms));
    }
	if (ms->count == 0)
        return (first_child(input, process, ms));
    else if (ms->count == ms->fork_n -1)
        return (last_child(input, process, ms));
    else
        return (middle_child(input, process, ms));
    return (0);
}
