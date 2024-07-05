
#include "minishell.h"


int check_cmd(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == ' ')
            return (1);
        i++;            
    }
    return (0);

}


int pipex(t_process_node *process, t_shell *ms)
{
    dprintf(2, "in pipex\n");
    while(ms->count < (ms->fork + 1))   
    {
        ms->execute = check_cmd(process->command[0]);//not sure if necessary
        
        // if (get_fd(process, ms) == -1)
        //     return (close_and_free(ms));

        get_fd(process, ms);
        
        // if (do_process(process, ms) == -1)
        //     return (close_and_free(ms));

        do_process(process, ms);

        close(ms->fd[0]);
        close(ms->fd[1]);
        ms->count++;
        process = process->next;//to next node
   }



}