/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:47 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/07 15:42:07 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/////////////////////////////////////////////////////////////////////

//char	*verify_path(char *cmd, t_process_node *process, t_shell *ms) 
char	*verify_path(char *cmd, t_shell *ms)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) != 0)
			//print_error_badcmd(cmd, pipex, EXIT_CMD_PERMMIT_ERR);
            set_exitcode(ms, 126);// error message "shell write error cmd string"
		if (access(cmd, F_OK) != 0)
			//print_error_badcmd(cmd, pipex, EXIT_CMD_NOT_FOUND);
            set_exitcode(ms, 127);// error message "command string not found:"
		return (ft_strdup(cmd));
	}
	return (NULL);
}



int get_path(t_process_node *process, t_shell *ms)
{
    int		i;
	char	*str;
	char	*command_path;

    command_path = verify_path(process->command[0], ms);
	if (process->cmd_path == NULL)
		return (0);
	i = -1;
	while (ms->envp != NULL && ms->envp[++i] != NULL)
	{
		str = ft_strjoin(ms->envp[i], "/");//may need to delete "envp:"
		command_path = ft_strjoin(str, process->command[0]);
		if (str)
			free(str);
		if (access(command_path, F_OK) == 0)
			break ;
		if (command_path)
			free(command_path);
		command_path = NULL;
	}
    process->cmd_path = command_path;
	return (0);
    
}


void do_dups(t_shell *ms)
{
    close(ms->read_end);
    dup2(ms->fd[0], STDIN_FILENO);
    dup2(ms->fd[1], STDOUT_FILENO);
    close(ms->fd[0]);
    close(ms->fd[1]);
}


int do_command(t_shell *ms, t_process_node *process)
{
    if (!process->builtin)//如果命令不是內建的，調用 do_dups 進行文件描述符的複製和關閉
        do_dups(ms);
    if (process->builtin)
        execute_builtin(ms, process);
        //return (execute_builtin(ms, process));// error check return (-1)

    if (get_path(process, ms))
        return (-1);
    execve(process->cmd_path, process->command, ms->envp);
	if (access(process->command[0], F_OK) == 0)
	{
		ft_printf("shell: %s: is a directory\n", process->command[0]);//need to fix error code
		return (set_exitcode(ms, 126));
	}
	ft_printf("shell: %s: Permission denied\n", process->command[0]);//need to fix error code
	return (set_exitcode(ms, 1));
}


int do_process(t_process_node *process, t_shell *ms)//處理命令的執行流程，包括處理內建命令和創建子進程
{
    if (ms->fork_n == 0 && process->builtin)
    {
        if (!ms->execute)
            return (ms->excode);
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
        else if (ms->pids[ms->count] == 0)
        {
            //data->sa.sa_handler = SIG_DFL;       signal
			//sigaction(SIGQUIT, &data->sa, NULL);
            if (ms->execute || do_command(ms, process))
                return (-1);
        }
    }    
   
   return (0); 
}