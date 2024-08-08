/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:54:59 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/07 17:13:01 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_exists(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	len = 0;
	while(name[i] && name[i] != '=')
		i++;
	key = ft_substr(name, 0, i + 1);
	if (!key)
		return (0); //should be error_handle
	len = ft_strlen(key);
	i = 0;
	while (i < ms->envp_size && ms->envp[i])
	{
		if ((ft_strncmp(key, ms->envp[i], len) == 0) 
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
			{
				free(key);
				return (1);// key is found
			}		
		i++;
	}
	free(key);
	return (0);
}


char *shrink(char *cmd, int remove) //if something after $ is invalid still print something before and after
{
	int i = 0;
	int j = 0;
	char *temp;
	char *new;
	
	new = ft_calloc(ft_strlen(cmd), sizeof(char)); //cannot be expanded, the delete the dollar sign
	if (!new)
		return (NULL);
	while(cmd[i] && i != remove) //shrink copy first part skip dollar sign and invalid env, copy rest of itif there is any and send it back
		new[j++] = cmd[i++];
	while (cmd[i] && cmd[i]!= ' ')
		i++;
	i++;
	new[j+1] = ' ';
	while(cmd[i - 1])
		new[j++] = cmd[i++];
	temp = cmd;
	cmd = new;
	free (temp);
	return (cmd);
}

char *add_value_back( char *value, int start, int len , char *cmd)//expand
{
	char *new;
	//char *temp; //had to comment out because of linux
	int i = 0;
	int j = 0;
	int		rest_of_str;
	
	new = ft_calloc((ft_strlen(cmd) - len + 1 + ft_strlen(value)) , sizeof(char));// cmd 長度  減 value + 1  + 新從envorinmental variables 找到得直
	while (i < start - 1)//copies echo "hello $USER" copies double quote hello_
	{
		new[i] = cmd[i];
		i++;
	}		
	j = 0;
	while(value[j])
		new[i++] = value[j++]; //hello yshu replace the $USER->yhsu	
	if(j < len)
		len = j;//? count the value
	rest_of_str = start + len; //$USER after that
	while(cmd[rest_of_str])
		new[i++] = cmd[rest_of_str++];
	free(cmd);
	cmd = new;
	return (new);
}

char	*find_value(t_shell *ms, char *key)
{
	int	i;
	int	len;
	char *value;

	i = 0;
	len = ft_strlen(key);
	while (ms->envp[i])
	{
		if(!ft_strncmp(key, ms->envp[i], ft_strlen(key)) && (ms->envp[i][len] == '\0'  || ms->envp[i][len] == '='))
		{
			value = (ft_strchr(ms->envp[i], '=') + 1); // USER=yhsu    value = yhsu
			return(value);
		}
		i++;
	}
	return (NULL);
}

char	*find_key_in_envp(t_shell *ms, char *key)
{
	int	i;

	i = 0;
	while (i < ms->envp_size) //iterates through the whole list
	{
		if (!key_exists(ms, key)) //doesn't match, then it will iterate through the list
			i++;
		else if (key_exists(ms, key)) //breaks if it equals or is at the end of list
			return (key);
	}
	return (NULL);
}
