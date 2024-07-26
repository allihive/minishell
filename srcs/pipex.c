/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:58:20 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/26 10:41:33 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int wait_children(t_shell *ms, int *pids, int count)
{
    int status;
    int i;
	int tmp;

    i = 0;
    // status = ms->excode;
	status = 0;
	tmp = ms->excode; //to store the old exit code?
   //ignore_signal();
//    printf("ms->excode in wait_children1 %d\n", ms->excode);
   while(i < count - 1)
   {
        if (pids[i] == -1)
        {   
            i++;
            continue;
        }
		if (pids[i] == 0)
		{
			// printf("exit code in waitchild1%d\n", ms->excode);
			return(ms->excode); //added this so that it would exit 42 echo $? = 42
		}
        waitpid(pids[i], &status, 0);//函式等待子進程結束並獲取其狀態。
        //dprintf(2, "wait_children\n");
        if (WIFEXITED(status))//如果子進程正常結束，設置 data->excode 為子進程的退出狀態。
		{
            ms->excode = WEXITSTATUS(status); // this is making everything turun to 0. entered as 42 and after sets it to 0
			// printf("ms->excode in wait_children1.5 %d\n", ms->excode);
		}
        else if (WIFSIGNALED(status)) //when I write exit it goes into here maybe segfaulting somewhere so it calls this
		{
            ms->excode = WTERMSIG(status) + 128;
			// printf("ms->excode in wait_children2 %d\n", ms->excode);
		}
        if (ms->excode == 131)
            ft_putstr_fd("^\\Quit: 3\n", 2);
        else if (ms->excode == 130)
            ft_putstr_fd("^C\n",2);
        i++;
   }
//    printf("ms->excode in wait_children2 %d\n", ms->excode);
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
    
   // dprintf(2, "im here count:%d fork:%d\n\n", ms->count, ms->fork_n);
   // ms->count = 0;
    while(ms->count < ms->fork_n)   
    //while (process != NULL)
    {
		//add data->execute = check_cmd
        while (ifisspace(*process->node_line))
			(process->node_line)++;
		
		dprintf(2, "in pipex process->node_line:%s\n", process->node_line);
		
		if (get_fd(process->node_line, process, ms) == -1)
            return (close_and_free(ms));//redirection

        
        // if (do_process(process, ms) == -1)
        //     return (close_and_free(ms));
        do_process(process, ms);
        if (ms->pids[ms->count] == 0)
            exit(0);

        close(ms->fd[0]);
        close(ms->fd[1]);
        //dprintf(2, "ms count pipex: %d\n", ms->count);
        ms->count++;
        if (process->next)
        {
            process = process->next;//to next node
        } 
    }
	// printf("ms->excode in pipex1 %d\n", ms->excode);
    wait_children(ms, ms->pids, (ms->fork_n + 1));
    //singal
	// printf("ms->excode in pipex2 %d\n", ms->excode);
    return (ms->excode);

}