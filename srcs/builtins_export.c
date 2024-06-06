/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:56:47 by alli              #+#    #+#             */
/*   Updated: 2024/06/05 15:13:28 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *name_exists(t_shell *ms, char *name)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (ms->envp[i])
	{
		if (ft_strncmp(name, ms->envp[i], len) == 0 && (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
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
		// error_handle(ms);
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
	while (i < ms->envp_size) //checking the whole envp size
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
	ms->envp_size += 1;
	new = ft_calloc(ms->envp_size, sizeof(char *));
	if (!new)
		error_handle(ms);
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[i], "_=", 2))//when shell is initally opened, there is _=bin/bash
		{
			new[i] = ft_strdup(name);//it will be replaced when there is something else written
			if (!new[i])
				error_handle(ms);
			i++;
		}
		new[i] = ft_strdup(ms->envp[j]);
		if (!new[i])
			// error_handle(ms);
		i++;
		j++;
	}
	ft_free_strs(ms->envp, 0, 0);
	ms->envp = new;
}

int	export_str_check(char *str)
{
	int i;
	
	i = 0;
	if (str[i] == ft_isdigit(str[i]))
		return (1);
	while (str[++i] && str[i] != '='  && 
			(ft_isalnum(str[i]) || str[i] == '_'))
		;
	if (str[i] == '\0')
		return (0);
	else 
		return (1);
}

int	export(t_shell *ms, char *cmd)//does cmd have to be a double pointer?
{
	int i;

	i = 0;
	if (!cmd[i])
		return (1);//envp_print
	if (!export_str_check(cmd))
	{
		if (name_exists(ms, cmd))
			envp_update(ms, cmd);
		else if (name_exists(ms, cmd) == NULL)
			envp_add(ms, cmd);
		//print string?
	}
	return(0);
}
