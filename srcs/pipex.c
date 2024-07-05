
#include "minishell.h"


int check_cmd(char *str)
{

    
    return (0);

}


int pipex(t_process_node *process, t_shell *ms)
{
    dprintf(2, "in pipex\n");
    while(ms->count < (ms->fork + 1))   
    {
        ms->execute = check_cmd(process->command[0]);
    
    
        
        
        ms->count++;
        process = process->next;//to next node
   }



}