/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:58:20 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/07 18:35:28 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int wait_children(t_shell *ms, int *pids, int count)
{
    int status;
    int i;

    i = 0;
    status = 0;
   //ignore_signal();
   while(i < count)
   {
        if (pids[i] == -1)
        {    
            i++;
            continue;
        }
        waitpid(pids[i], &status, 0);//函式等待子進程結束並獲取其狀態。
        if (WIFEXITED(status))//如果子進程正常結束，設置 data->excode 為子進程的退出狀態。
            ms->excode = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            ms->excode = WTERMSIG(status) + 128;
        if (ms->excode == 131)
            ft_putstr_fd("^\\Quit: 3\n", 2);
        else if (ms->excode == 130)
            ft_putstr_fd("^C\n",2);      
        i++;
   }
   return (ms->excode);
}


int check_cmd(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i])
            return (1);
        i++;            
    }
    return (0);

}


int pipex(t_process_node *process, t_shell *ms)
{
   
    while(ms->count < (ms->fork_n + 1))   
    {
        ms->execute = check_cmd(process->command[0]);//not sure if necessary
        
        // if (get_fd(process, ms) == -1)
        //     return (close_and_free(ms));

        //get_fd(process, ms);
        
        // if (do_process(process, ms) == -1)
        //     return (close_and_free(ms));
        //dprintf(2, "in pipex1\n");
        do_process(process, ms);
        //dprintf(2, "in pipex2\n");
        close(ms->fd[0]);
        close(ms->fd[1]);
        ms->count++;
        process = process->next;//to next node
   }
    wait_children(ms, ms->pids, (ms->fork_n + 1));
    //singal
    return (ms->excode);

}