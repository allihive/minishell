/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:28 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/05 21:41:24 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_heredocs(t_process_node *process,t_shell *ms);


int	set_exitcode(t_shell *ms, int exitcode)
{
	ms->excode = exitcode;
	return (-1);
}

int first_child(t_process_node *process, t_shell *ms)
{
    if (pipe(ms->fd)== -1)
    {
        ft_putstr_fd("lobster-shell 🦞:error opening a pipe\n", 2);
        return(set_exitcode(ms, -1));
    }
    ms->read_end = dup(ms->fd[0]);    
    close(ms->fd[0]);
    if (handle_heredocs(process, ms) == -1)
        return (-1);
    return (handle_redirects(process, ms));
        
}

int middle_child(t_process_node *process, t_shell *ms)
{
    int tmp_fd;
    
    if (pipe(ms->fd)== -1)
    {
        ft_putstr_fd("lobster-shell 🦞:error opening a pipe\n", 2);
        return(set_exitcode(ms, -1));
    }
    tmp_fd = dup(ms->read_end);
    dup2(ms->fd[0], ms->read_end);
    dup2( tmp_fd,fd[0]);// use fd[0] to open the file which opened by tmp_fd 
    close(tmp);
    if (handle_heredocs(process, ms) == -1)
        return (-1);
    return (handle_redirects(process, ms));

}

int last_child(t_process_node *process, t_shell *ms)
{
    //last child no pipe
    dup2(ms->read_end, ms->fd[0]);
    close(ms->read_end);
    ms->fd[1] = dup(STDOUT_FILENO);
    if (handle_heredocs(process, ms)== -1)
        return (-1);
    return (handle_redirects(process, ms));
    
}



int get_fd(t_process_node *process, t_shell *ms)
{
    if (ms->fork_n == 0)//command == 0
    {
        if (handle_heredocs(process, ms) == -1)
            return (-1);
        return (handle_redirects(process, ms));
    }
    if (ms->count == 0)
        return (first_child(process, ms));
    else if (ms->count == ms->fork_n)
        return (last_child(process, ms));
    else
        return (middle_child(process, ms));
}