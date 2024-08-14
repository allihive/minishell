/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:57:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 12:42:05 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*verify_path(char *cmd, t_shell *ms)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) != 0)
		{
			error_msg(cmd, 0, "No such file or directory", ms->excode = 126);
			close_and_free(ms);
		}
		if (access(cmd, X_OK) != 0)
		{
			error_msg(cmd, 0, "Permission denied", ms->excode = 126);
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

int	get_the_path(t_process_node *process,
	t_shell *ms, char	*command_path, int i)
{
	char	*str;

	if (ms->envp_paths)
	{
		while (ms->envp_paths != NULL && ms->envp_paths[++i] != NULL)
		{
			str = ft_strjoin(ms->envp_paths[i], "/");
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

int	get_path(t_process_node *process, t_shell *ms)
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
