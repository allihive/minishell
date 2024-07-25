/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:47 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/25 16:41:53 by yhsu             ###   ########.fr       */
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
	dprintf(2, "in get path process->command[0]: %s\n", process->command[0]);
	dprintf(2, "in get path process->command[1]: %s\n", process->command[1]);
    init_envp_path(ms->envp, ms);
	
    command_path = verify_path(process->command[0], ms);
    //dprintf(2, "command_path: %s\n", command_path);
	if (command_path != NULL)
    {
        process->cmd_path = command_path;
        return (0);
    }
		
	i = -1;
	while (ms->envp_paths != NULL && ms->envp_paths[++i] != NULL)
	{
		str = ft_strjoin(ms->envp_paths[i], "/");//may need to delete "envp:"
		//dprintf(2, "ms->envp[i]: %s\n", ms->envp[i]);
        command_path = ft_strjoin(str, process->command[0]);
		if (str)
			free(str);
		if (access(command_path, F_OK) == 0)
			break ;
		if (command_path)
			free(command_path);
		command_path = NULL;
	}
    //dprintf(2, "command_path-end: %s\n", command_path);
    process->cmd_path = command_path;
	return (0);
    
}

int	call_builtin(t_shell *ms, t_process_node *node)
{
	//printf("ms->excode before in call builtin %d\n", ms->excode);
	if (ft_strncmp(node->command[0], "export", 6) == 0)
		ft_export(ms, node->command, 1); //added 1 for fd
	else if (ft_strncmp(node->command[0], "unset", 5) == 0)
		unset(ms, node->command);
	else if(ft_strncmp(node->command[0], "exit", 4) == 0)
	{
		printf("goes into ft_exit\n");
		ft_exit(ms, node->command);
		// printf("ms->excode in call builtin after func %d\n", ms->excode);
	}
	else if (node->command[0][0] == 'p' || node->command[0][0] == 'P') //doesn't work on linux with capitals
	{
		if (check_case(node->command[0], "pwd"))//PWD pwD
			pwd(ms, 0,  ms->fd[1]);
	}
	else if (node->command[0][0] == 'e' || node->command[0][0] == 'E') //shouldn't need the capital E doesn't work on linux
	{
		if (check_case(node->command[0], "env"))
			env(ms, 1); //added 1 for fd
		else if (check_case(node->command[0], "echo"))
			echo(ms, node->command, 1);//added 1 for fd
	}
    else if (ft_strncmp(node->command[0], "cd", 2) == 0)
		cd(ms, node->command, 0, 0);
	return (ms->excode);
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
        //dprintf(2, "1 command:%s, builtin:%d\n", process->command[0],process->builtin);
		// printf("ms->excode do_command %d\n", ms->excode);
        return (ms->excode = call_builtin (ms, process));
    }
    
    if (get_path(process, ms))
        return (-1);

    
    //dprintf(2, "process->cmd_path: %s\n", process->cmd_path);
    //dprintf(2, "process->command[0]: %s\n", process->command[0]);
    //dprintf(2, "process->command[1]: %s\n", process->command[1]);
   dprintf(2, "2 command:%s, builtin:%d\n", process->command[0],process->builtin);
    execve(process->cmd_path, process->command, ms->envp);
	if (access(process->command[0], F_OK) == 0)
	{
		ft_printf("🦞shell: %s: is a directory\n", process->command[0]);//need to fix error code
		return (set_exitcode(ms, 126));
	}
	ft_printf("🦞shell: %s: Permission denied\n", process->command[0]);//need to fix error code
	//dprintf(2, "do command3\n");
    return (set_exitcode(ms, 1));
}


int do_process(t_process_node *process, t_shell *ms)//處理命令的執行流程，包括處理內建命令和創建子進程
{
    
	//dprintf(2, "process->builtin:%d\n", process->builtin);
    //dprintf(2, "ms->fork:%d\n", ms->fork_n);
    //dprintf(2, "ms->count:%d\n", ms->count);
    if (ms->fork_n == 1 && process->builtin )
    {
       
        //if (!ms->execute)
            //return (ms->excode);// need to check excode
        if (do_command(ms, process) == -1)
            return (-1);
		// printf("ms->excode do_process %d\n", ms->excode);
    }
    else //create child process
    {
        //dprintf(2, "in do prcess else \n");
        ms->pids[ms->count] = fork();
		//dprintf(2, "in do prcess fork: %d, pids: %d \n",ms->count, ms->pids[ms->count]);
        if (ms->pids[ms->count] < 0)
        {
            //dprintf(2, "in do process 0\n");
            ft_putstr_fd("shell: error: fork failed\n", 2);
			return (set_exitcode(ms, -1));
        }
        if (ms->pids[ms->count] == 0)
        {
            //dprintf(2,"in child\n");
			//data->sa.sa_handler = SIG_DFL;       signal
			//sigaction(SIGQUIT, &data->sa, NULL);
            //dprintf(2, "in do process 1\n");
            //do_command(ms, process);
            if (ms->execute || do_command(ms, process))
            	return (-1);
        }
		
    }
   return (ms->excode); 
}