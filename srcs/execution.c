/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:47 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/09 12:22:50 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void do_dups(t_shell *ms)
{
    if (ms->read_end >= 0)
		close(ms->read_end);
	ms->read_end = -1;
    dup2(ms->fd[0], 0);// stdinput
    dup2(ms->fd[1], 1);//stdoutput
    if (ms->fd[0] >= 0)
		close(ms->fd[0]);
	ms->fd[0] = -1;
    if (ms->fd[1] >= 0)
		close(ms->fd[1]);
	ms->fd[1] = -1;
}


int do_command(t_shell *ms, t_process_node *process)
{
    if (!process->builtin)//如果命令不是內建的，調用 do_dups 進行文件描述符的複製和關閉
        do_dups(ms);
    if (process->builtin)
        return (ms->excode = call_builtin (ms, process));
    if (get_path(process, ms))
        return (-1);
    execve(process->cmd_path, process->command, ms->envp);
	if (access(process->command[0], F_OK) == 0)
	{
		error_msg(process->command[0], 0, "is a directory", ms->excode = 126);//need to fix error code
		return (-1);
	}
	ft_putstr_fd(process->command[0], 2);
	ft_putstr_fd(" Permission denied\n", 2);
    return (set_exitcode(ms, 1));
}


int do_process(t_process_node *process, t_shell *ms)//處理命令的執行流程，包括處理內建命令和創建子進程
{
    if (ms->fork_n == 1 && process->builtin )
    {
        if (do_command(ms, process) == -1)
            return (-1);
    }
    else //create child process
    {
        ms->pids[ms->count] = fork();
        if (ms->pids[ms->count] < 0)
        {
            ft_putstr_fd("shell: error: fork failed\n", 2);
			return (set_exitcode(ms, -1));
        }
        if (ms->pids[ms->count] == 0)
        {
            if (do_command(ms, process))
            	return (-1);
        }
    }
   return (ms->excode); 
}

