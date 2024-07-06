/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:41:29 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/06 18:08:51 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exitcode(t_ms *ms, int exitcode)
{
	ms->excode = exitcode;
	return (-1);
}

void redir_append(char *redirectappend, t_shell *ms)
{
	int		i;

	i = 1;
	//if (validate_redir(data, redir) == -1)
		//return (-1);
	close(ms->ends[1]);
	if ((*redir)[1] == '>')//>>
		ms->ends[1] = open(redirectappend, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ms->ends[1] < 0)
	{
		if (access(redirectappend, F_OK) != 0)
			ft_printf( "shell: %s: No such file or directory\n", redirectappend);//need to fix fd 2
		else
			ft_printf( "shell: %s: Permission denied\n", redirectappend);//need to fix fd 2
		ms->execute = 0;
		set_exitcode(data, -1);
	}
	
}



void redir_out(char *redirectout, t_shell *ms)
{
	int		i;

	i = 1;
	//if (validate_redir(data, redir) == -1)
		//return (-1);
	close(ms->ends[1]);
	if ((*redir)[1] == '>')//>>
		ms->ends[1] = open(redirectout, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ms->ends[1] < 0)
	{
		if (access(redirectout + 1, F_OK) != 0)
			ft_printf( "shell: %s: No such file or directory\n", redirectout);//need to fix fd 2
		else
			ft_printf( "shell: %s: Permission denied\n", redirectout );//need to fix fd 2
		ms->execute = 0;
		set_exitcode(data, -1);
	}
	
}



void redir_in(char *redirectin,t_shell *ms)
{
    //if (validate_redir(data, redir) == -1)
		//set_exitcode(data, -1);
	close(ms->fd[0]);
	ms->fd[0] = open(redirectin, O_RDONLY);
	if (ms->fd[0] < 0)
	{
		if (access(redirectin, F_OK) != 0)
			ft_printf( "shell: %s: No such file or directory\n",redirectin);// need to fix fd 2
		else
			ft_printf( "shell: %s: Permission denied\n", redirectin);// need to fix fd 2
		ms->execute = 0;
		set_exitcode(data, -1);// need to check
	}
}


// int handle_redirects(t_process_node *process, t_shell *ms)
// {
//     int i;
    
//     i = 0;
//     if (process->redirectin == 1)//<redirect in
//     {
//         while (process->redirect_in[i])
//         {
//             if (redir_in(process->redirect_in[i], ms) == -1)
// 				return (ms->exitcode);
//             i++
//         }  
//     }
//     else if (process->append == 1)//>>append
//     {
//         if (process->append_s && redir_in(process->append_s, ms) == -1)
//             return (ms->exitcode);
//     }
//     else if (process->redirectout == 1)//> redirect out
//     {
//         while (process->redirect_out[i])
//         {
//             if (redir_in(process->redirect_in[i], ms) == -1)
// 				return (ms->exitcode);
//             i++
//         }
//     } 
// }

