/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:57:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/01 19:03:11 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*verify_path(char *cmd, t_shell *ms)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) != 0)
		{
			//print_error_badcmd(cmd, pipex, EXIT_CMD_NOT_FOUND);
            error_msg(cmd, 0, "No such file or directory", 127, ms);
			close_and_free(ms);
		}
		if (access(cmd, X_OK) != 0)//./infile  when no permisssion to access 0000
 		{
            error_msg(cmd, 0, "Permission denied", 126, ms);
			close_and_free(ms);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

static char	**get_env_paths(char **envp, t_shell *ms)
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
		print_error_and_free("minishell: malloc error", ms);
	return (env_paths);
}


// static void	init_envp_path(char **envp, t_shell *ms)
// {
// 	char	**arr;

// 	//dprintf(2, "envp[0]:%s\n", envp[0]);
// 	//dprintf(2, "envp[1]:%s\n", envp[1]);
// 	if (*envp == NULL)
// 	{
// 		arr = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", ':');
// 		if (arr == NULL)
// 			perror("error malloc");
//             //print_error("error malloc", pipex, EXIT_FAILURE);
// 		ms->envp_paths = arr;
// 	}
// 	else
// 	{
// 		ms->envp_paths = get_env_paths(envp, ms);
// 	}
// }

int get_the_path(t_process_node *process, t_shell *ms, char	*command_path, int i)
{
	char	*str;
	
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
	

int get_path(t_process_node *process, t_shell *ms)// get_path_cmd
{
    int		i;
	char	*command_path;

    if (!process->command[0])
		return (-1);
	ms->envp_paths = get_env_paths(ms->envp, ms);
   	command_path = verify_path(process->command[0], ms);
	if (command_path != NULL)
    	return (process->cmd_path = command_path, 0);
	i = -1;
	if (get_the_path(process, ms, command_path, i) == -1)
		return (-1);
	return (0);
}
