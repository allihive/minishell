/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:56:47 by alli              #+#    #+#             */
/*   Updated: 2024/06/21 10:46:29 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *name_exists(t_shell *ms, char *name)
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
			{
				printf("name exists returns: %s\n", ms->envp[i] + len);
				return (ms->envp[i] + len);
			}
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
	printf("entered envp_update");
	while (name[len] != '=')
		len++;
	while (ms->envp[i]) //checking the whole envp size
	{
		if (!ft_strncmp(ms->envp[i], name, len)) // returns 0 when it matches
			break ;
		i++;
	}
	if (ms->envp[i][len] == '=') //check if say here= (len = 5)
	{
		ft_bzero(ms->envp[i], ft_strlen(name));//give it a null space in the string the length of the name
		ms->envp[i] = ft_strjoin(ms->envp[i], name);//this should be nulled and replaced.
		if (!ms->envp[i]) //malloc check
			error_handle(ms);
	}
}

void envp_add(t_shell *ms, char *name)
{
	char	**new;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	// (void)name;
	ms->envp_size += 1;
	new = ft_calloc((ms->envp_size + 1), sizeof(char *));//check how big this should be
	if (!new)
		error_handle(ms);
	while (i < ms->envp_size - 1  && ms->envp[i])
	{
		if (ft_strncmp(ms->envp[i], "_=", 2) == 0)//when shell is initally opened, there is _=bin/bash
		{
			new[i] = ft_strdup(name);//it will be replaced when there is something else written
			if (!new[i])
				error_handle(ms);
		}
		else
		{
			new[i] = ft_strdup(ms->envp[j]);
			if (!new[i])
			{
				// error_handle(ms);
			printf("nothing malloced");
			}
		}
		i++;
		j++;
	}
	// new[i] = 
	ft_free_strs(ms->envp, 0, 0);
	ms->envp = new;
}

int	export_str_check(char *str)
{
	int i;
	
	i = 0;
	if (str[i] == ft_isdigit(str[i]))
		return (1);
	while (str[i] && str[i] != '='  && 
			(ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '=')
		return (0);
	else 
		return (1);
}

int	ft_export(t_shell *ms, char **cmd)//works with single pointer but nt a double pointer
{
	int i;

	i = 0;
	
	if (cmd[1] == NULL)
		envp_print(ms);
	else if (!export_str_check(cmd[1]) && ms->envp[i])
	{
		if (name_exists(ms, cmd[1]))
		{
			printf("before envp_update\n"); //delete comment
			envp_update(ms, cmd[1]);
		}
		if (name_exists(ms, cmd[1]) == NULL)
		{
			printf("before add_envp\n"); //delete comment
			envp_add(ms, cmd[1]);
			printf("added envp\n");//delete comment
		}
	}
	return(0);
}
