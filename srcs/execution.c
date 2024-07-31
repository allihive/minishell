/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:47 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/31 17:33:31 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//char	*verify_path(char *cmd, t_process_node *process, t_shell *ms) 
char	*verify_path(char *cmd, t_shell *ms)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) != 0)
		{
			//print_error_badcmd(cmd, pipex, EXIT_CMD_NOT_FOUND);
            ft_putstr_fd("Command '", 2);//EXIT_CMD_NOT_FOUND
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("' not found\n", 2);
			ms->excode = 127;// error message "command string not found:"
			close_and_free(ms);
		}
		if (access(cmd, X_OK) != 0)//./infile  when no permisssion to access 0000
 		{
			//print_error_badcmd(cmd, pipex, EXIT_CMD_PERMMIT_ERR);
            ft_putstr_fd("shell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(" Permission denied\n", 2);
			ms->excode = 126;// EXIT_CMD_PERMMIT_ERR)
			close_and_free(ms);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

char	**get_env_paths(char **envp)
{
	char	*path_line;
	char	**env_paths;
	int		i;

	path_line = NULL;
	while (*envp != NULL)
	{
		if (ft_strnstr(*envp, "PATH=", 5) != NULL)
		{
			path_line = *envp;
			break ;
		}
		envp++;
	}
	if (path_line == NULL)
		return (NULL);
	i = -1;
	while (++i < 5)
		path_line++;
	env_paths = ft_split(path_line, ':');
	if (env_paths == NULL)
		perror("malloc error");
        //print_error_partial_free("malloc error", pipex);
	return (env_paths);
}


void	init_envp_path(char **envp, t_shell *ms)
{
	char	**arr;

	
	dprintf(2, "envp[0]:%s\n", envp[0]);
	dprintf(2, "envp[1]:%s\n", envp[1]);
	if (*envp == NULL)
	{
		arr = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", ':');
		if (arr == NULL)
			perror("error malloc");
            //print_error("error malloc", pipex, EXIT_FAILURE);
		ms->envp_paths = arr;
	}
	else
	{
		ms->envp_paths = get_env_paths(envp);
	}
}


int get_path(t_process_node *process, t_shell *ms)// get_path_cmd
{
    int		i;
	char	*str;
	char	*command_path;

    if (!process->command[0])
		return (-1);
    //init_envp_path(ms->envp, ms);
	ms->envp_paths = get_env_paths(ms->envp);
   	command_path = verify_path(process->command[0], ms);
	if (command_path != NULL)
    	return (process->cmd_path = command_path, 0);
	i = -1;
	
	if (ms->envp_paths)
	{
		while (ms->envp_paths != NULL && ms->envp_paths[++i] != NULL)
		{
			str = ft_strjoin(ms->envp_paths[i], "/");//may need to delete "envp:"
			command_path = ft_strjoin(str, process->command[0]);
			
			if (str)
				free(str);
			if (access(command_path, F_OK) == 0)
			{
				process->cmd_path = command_path;
				//break;
				return (0);
			}
			if (command_path)
				free(command_path);
			command_path = NULL;
		}
		process->cmd_path = command_path;
		cmd_not_found(process->command[0], ms);
		close_and_free(ms);
		return (-1);
	}
	return (0);
}


void do_dups(t_shell *ms)
{
    close(ms->read_end);
    dup2(ms->fd[0], 0);// stdinput
    dup2(ms->fd[1], 1);//stdoutput
    close(ms->fd[0]);
    close(ms->fd[1]);
}


int do_command(t_shell *ms, t_process_node *process)
{
    
    if (!process->builtin)//如果命令不是內建的，調用 do_dups 進行文件描述符的複製和關閉
        do_dups(ms);
    if (process->builtin)
    {
        return (ms->excode = call_builtin (ms, process));
    }
    if (get_path(process, ms))
        return (-1);
   //dprintf(2, "2 command:%s, builtin:%d\n", process->command[0],process->builtin);
    execve(process->cmd_path, process->command, ms->envp);
	if (access(process->command[0], F_OK) == 0)
	{
		error_msg(process->command[0] ,0, "is a directory");//need to fix error code
		return (set_exitcode(ms, 126));
	}
	ft_putstr_fd(process->command[0],2);
	ft_putstr_fd(" Permission denied\n", 2);

    return (set_exitcode(ms, 1));
}


int do_process(t_process_node *process, t_shell *ms)//處理命令的執行流程，包括處理內建命令和創建子進程
{
    if (ms->fork_n == 1 && process->builtin )
    {
        //if (!ms->execute)
            //return (ms->excode);// need to check excode
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
			//data->sa.sa_handler = SIG_DFL;       signal
			//sigaction(SIGQUIT, &data->sa, NULL);
            if (ms->execute || do_command(ms, process))
            	return (-1);
        }
    }
   return (ms->excode); 
}
