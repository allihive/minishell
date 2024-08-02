/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:41:29 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/02 15:04:10 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redir_append(char *redirectappend, t_shell *ms, int j)
{
	int		i;
	
	i = 0;
	while (ifisspace(*redirectappend))
		redirectappend++;
	
	if (validate_redir_append(ms, redirectappend + i, j) == -1)
		return (-1);
	
	close(ms->fd[1]);
	if (ms->list->append == 1)
		ms->fd[1] = open(ms->list->append_s[j], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (ms->fd[1] < 0)
	{
		if (access(ms->list->append_s[j], F_OK) != 0)
			ft_printf( "shell: %s: No such file or directory\n", redirectappend);//need to fix fd 2
		else
			ft_printf( "shell: %s: Permission denied\n", redirectappend);//need to fix fd 2
		//ms->execute = 0;
		return (set_exitcode(ms, -1));
	}
	return (0);
}

int redir_out(char *redirectout, t_shell *ms, int j)
{
	int		i;

	i = 0;
	while (ifisspace(redirectout[i]) == 1)
		i++;
	if (validate_redir_out(ms, redirectout + i, j) == -1)
		return (-1);
	close(ms->fd[1]);
	if (redirectout)//>>
		ms->fd[1] = open(ms->list->redirect_out[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ms->fd[1] < 0)
	{
		if (access(ms->list->redirect_out[j], F_OK) != 0)
			ft_printf( "shell: %s: No such file or directory\n", redirectout);//need to fix fd 2
		else
			ft_printf( "shell: %s: Permission denied\n", redirectout );//need to fix fd 2
		return (set_exitcode(ms, -1));
	}
	return (0);
}

int redir_in(char *redirectin, t_shell *ms, int j)
{
	if (validate_redir_in(ms, redirectin, j) == -1)
		return (-1);
	close(ms->fd[0]);
	ms->fd[0] = open(ms->list->redirect_in[j], O_RDONLY);
	//ms->fd[0] = open(redirectin, O_RDONLY);
	if (ms->fd[0] < 0)
	{
		if (access(ms->list->redirect_in[j], F_OK) != 0)
			error_msg(ms->list->redirect_in[j], 0, "No such infile or directory", 1, ms);
		else
			error_msg(ms->list->redirect_in[j], 0, "Permission denied", 1, ms);
		ms->execute = 0;
		return (set_exitcode(ms, -1));// need to check
	}
	return (0);
	
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

