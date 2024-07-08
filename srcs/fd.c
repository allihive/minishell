/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:28 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/08 14:35:41 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_heredocs(t_process_node *process,t_shell *ms);


int	set_exitcode(t_shell *ms, int exitcode)
{
	ms->excode = exitcode;
	return (-1);
}

char *first_child(char *input, t_process_node *process, t_shell *ms)
{
    dprintf(2, "checkfirst\n");
    if (pipe(ms->fd)== -1)
    {
       
        //close_fds(pipex);
        //print_error("pipe error", pipex, 1);

         perror("pipe error");// need to fix
        
    }
    ms->read_end = dup(ms->fd[0]);    
    close(ms->fd[0]);
    // if (handle_heredocs(process, ms) == -1)
    //     return (-1);
    //return (handle_redirects(process, ms));
    
    return (go_check_redirect(input, process, ms));    
}

char *middle_child(char *input, t_process_node *process, t_shell *ms)
{
    int tmp_fd;
    
    dprintf(2, "checkmiddle\n");
    if (pipe(ms->fd)== -1)
    {
         //close_fds(pipex);
        //print_error("pipe error", pipex, 1);
        perror("pipe error");// need to fix
    }
    tmp_fd = dup(ms->read_end);
    dup2(ms->fd[0], ms->read_end);
    dup2( tmp_fd, ms->fd[0]);// use fd[0] to open the file which opened by tmp_fd 
    close(tmp_fd);
    // if (handle_heredocs(process, ms) == -1)
    //     return (-1);
    //return (handle_redirects(process, ms));
    return (go_check_redirect( input, process, ms));
}

char *last_child(char *input,t_process_node *process, t_shell *ms)
{
    dprintf(2, "checklast\n");
    //last child no pipe
    dup2(ms->read_end, ms->fd[0]);
    close(ms->read_end);
    ms->fd[1] = dup(STDOUT_FILENO);
    // if (handle_heredocs(process, ms)== -1)
    //     return (-1);
   
    return (go_check_redirect(input, process, ms));
}

char *get_fd(char *input, t_process_node *process, t_shell *ms)
{
    if (ms->fork_n == 1)//command == 1
    {
        // if (handle_heredocs(process, ms) == -1)
        //     return (-1);
        //return (handle_redirects(process, ms));
        
        return (go_check_redirect(input, process, ms));
    }
    dprintf(2, "ms count: %d\n", ms->count);
    if (ms->count == 0)
        return (first_child(input, process, ms));
    else if (ms->count == ms->fork_n -1)
        return (last_child(input, process, ms));
    else
        return (middle_child(input, process, ms));
    return (0);
}