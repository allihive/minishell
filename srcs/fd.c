/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:28 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/25 16:17:22 by yhsu             ###   ########.fr       */
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
    dprintf(2, "checkfirst\n");
    
    if (pipe(ms->fd)== -1)
    {
       
        ft_putstr_fd( "shell: error opening a pipe\n", 2);
		return (set_exitcode(ms, -1));
        
    }
    dprintf(2, "checkfirst 1\n");
    ms->read_end = dup(ms->fd[0]);    
    close(ms->fd[0]);

    //close(ms->fd[1]);
    
    //dprintf(2, "first_child: ms->fd[1] = %d, ms->read_end = %d\n", ms->fd[1], ms->read_end);
    
    // if (handle_heredocs(input, process, ms) == -1)
    //     return (-1);
    
    return (go_check_redirect(input, process, ms));    
}

int middle_child(char *input, t_process_node *process, t_shell *ms)
{
    int tmp_fd;
    
    dprintf(2, "checkmiddle\n");
   
    if (pipe(ms->fd)== -1)
    {
        ft_putstr_fd("shell: error opening a pipe\n", 2);
		return (set_exitcode(ms, -1));
    }
    tmp_fd = dup(ms->read_end);
    dup2(ms->fd[0], ms->read_end);
    dup2( tmp_fd, ms->fd[0]);// use fd[0] to open the file which opened by tmp_fd 
    close(tmp_fd);

    // close(ms->fd[0]);
    // close(ms->fd[1]);

    // if (handle_heredocs(input, process, ms) == -1)
    //     return (-1);

    return (go_check_redirect(input, process, ms));
}

int last_child(char *input,t_process_node *process, t_shell *ms)
{
    dprintf(2, "checklast\n");
    
    //last child no pipe
    dup2(ms->read_end, ms->fd[0]);
    close(ms->read_end);
    ms->fd[1] = dup(1);
    // if (handle_heredocs(input, process, ms)== -1)
    //     return (-1);
     //dprintf(2, "last_child: ms->fd[0] = %d, ms->fd[1] = %d\n", ms->fd[0], ms->fd[1]);
   
    return (go_check_redirect(input, process, ms));
}

int get_fd(char *input, t_process_node *process, t_shell *ms)
{
    dprintf(2, "input in get_fd: %s\n", input);
	dprintf(2, "fork_n in get_fd: %d\n", ms->fork_n);
    if (ms->fork_n == 1)//command == 1
    { 
         dprintf(2, "in if condition in get fd\n");
		return (go_check_redirect(input, process, ms));
    }
    //dprintf(2, "ms count: %d\n", ms->count);
    dprintf(2, "get fd2\n") ;
	if (ms->count == 0)
        return (first_child(input, process, ms));
    else if (ms->count == ms->fork_n -1)
        return (last_child(input, process, ms));
    else
        return (middle_child(input, process, ms));
    return (0);
}