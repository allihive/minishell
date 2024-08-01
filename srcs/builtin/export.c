/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:56:47 by alli              #+#    #+#             */
/*   Updated: 2024/08/01 14:32:12 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *name_exists_env(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	while(name[i] && name[i] != '=')
		i++;
	key = ft_substr(name, 0, i + 1);
	if (!key)
		return (NULL); //should be error_handle
	len = ft_strlen(key + 1);
	i = 0;
	while (i < ms->envp_size && ms->envp[i])
	{
		if ((ft_strncmp(key, ms->envp[i], len) == 0) 
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
				return (ms->envp[i] + len);
		i++;
	}
	return (NULL);
}

char *env_exists(char *name, t_shell *ms)
{
	char	*tmp;
	int		len;
	int 	i;
	
	i = 0;
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		error_handle(ms);
	len = ft_strlen(tmp);
	while (ms->envp[i] && !ft_strnstr(ms->envp[i], tmp, len))//make sure the string is not there.
		i++;
	if (ms->envp[i] != NULL)
		return (ms->envp[i] + len);
	return (NULL);
}

void envp_update(t_shell *ms, char *name)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (name[len] != '=')
		len++;
	while (ms->envp[i]) //checking the whole envp size
	{
		if (name_exists_env(ms, name)) // ft_strncmp(ms->envp[i], name, len) == 0 && 
			break ;
		i++;
	}
	if (ms->envp[i][len] == '=') //check if say here= (len = 5)
	{
		ft_memset(ms->envp[i], 0, ft_strlen(name));//give it a null space in the string the length of the name
		ms->envp[i] = ft_strjoin(ms->envp[i], name);//this should be nulled and replaced.
		if (!ms->envp[i]) //malloc check
			close_and_free(ms);
	}
}

static char	*latest_envp(char *name)
{
	char	*new_str;

	if (ft_strchr(name, '='))
	{
		new_str = ft_strdup(name);
		if (!new_str)
			return (NULL); //error message
		return (new_str);
	}
	new_str = ft_strjoin(name, "=");
	if (!new_str)
		return (NULL); //error_message
 	return (new_str);
}

char *add_to_end_of_list(t_shell *ms, char *name, int i, int j)
{
	char *new;
	
	new = ft_calloc((ms->envp_size), sizeof(char *));//check how big this should be
	if (!new)
		error_handle(ms);
	if (ft_strncmp(ms->envp[i], "_=", 2) == 0)//when shell is initally opened, there is _=bin/bash
	{
		new = latest_envp(name);//it will be replaced when there is something else written
		if (!new)
			error_handle(ms);
		ms->flag = 1;
		return (new);
	}
	else
	{
		new = ft_strdup(ms->envp[j]);//add elements that are already in the list
		if (!new)
			return (NULL);// error_handle(ms);
	}
	return (new);
}

void envp_add(t_shell *ms, char *name)
{
	char	**new;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	ms->envp_size += 1;
	ms->flag = 0;
	if (!name)
		close_and_free(ms); //should be some type of error close and free?
	new = ft_calloc((ms->envp_size), sizeof(char *));//check how big this should be
	if (!new)
		error_handle(ms);
	while (i < ms->envp_size - 1 && ms->envp[i])
	{
		new[i] = add_to_end_of_list(ms, name, i, j);
		i++;
		j++;
	}
	if (name && !ms->flag)
		new[i] = latest_envp(name);
	ft_free_strs(ms->envp, 0, 0);
	ms->envp = new;
}

static int	export_str_check(char *str)
{
	int i;
	
	i = 0;
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '='  && 
			(ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (0);
}

int	cmd_counter(char **cmd)
{
	int	cmd_args;
	
	cmd_args = 0;
	while (cmd[cmd_args])
	{
		cmd_args++;
	}
	return (cmd_args);
}
void	update_or_add_envp(t_shell *ms, char **cmd, int j, int flag)
{
	if (name_exists_env(ms, cmd[j]))
		envp_update(ms, cmd[j]);
	if (name_exists_env(ms, cmd[j]) == NULL)
		envp_add(ms, cmd[j]);
	if (flag == 0)
		ms->excode = 0;
}

int	ft_export(t_shell *ms, char **cmd, int fd)
{
	int i;
	int	j;
	int	cmd_args;
	int	flag;

	i = 0;
	j = 1;
	flag = 0;

	cmd_args = cmd_counter(cmd);
	if (cmd_args == 1)
		envp_print(ms, fd);
	while (j < cmd_args)
	{
		if(export_str_check(cmd[j]) && ms->envp[i])
		{
			error_msg(cmd[0], cmd[j], "not a valid identifier", 1, ms);
			flag = 1;
		}
		if (!export_str_check(cmd[j]) && ms->envp[i])
			update_or_add_envp(ms, cmd, j, flag);
		j++;
	}
	return(ms->excode);
}

