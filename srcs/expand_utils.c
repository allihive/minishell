/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:54:59 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 14:07:44 by alli             ###   ########.fr       */
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
	while (name[i] && name[i] != '=')
		i++;
	key = ft_substr(name, 0, i + 1);
	if (!key)
		return (0);
	len = ft_strlen(key);
	i = 0;
	while (i < ms->envp_size && ms->envp[i])
	{
		if ((ft_strncmp(key, ms->envp[i], len) == 0)
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
		{
			free(key);
			return (1);
		}
		i++;
	}
	free(key);
	return (0);
}

char	*shrink(char *cmd, int remove)
{
	int		i;
	int		j;
	char	*temp;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(cmd), sizeof(char));
	if (!new)
		return (NULL);
	while (cmd[i] && i != remove)
		new[j++] = cmd[i++];
	while (cmd[i] && cmd[i] != ' ')
		i++;
	i++;
	new[j + 1] = ' ';
	while (cmd[i - 1])
		new[j++] = cmd[i++];
	temp = cmd;
	cmd = new;
	free (temp);
	return (cmd);
}

char	*add_value_back(char *value, int start, int len, char *cmd)
{
	char	*new;
	int		i;
	int		j;
	int		rest_of_str;

	i = 0;
	j = 0;
	new = ft_calloc((ft_strlen(cmd) - len
				+ 1 + ft_strlen(value)), sizeof(char));
	while (i < start - 1)
	{
		new[i] = cmd[i];
		i++;
	}		
	j = 0;
	while (value[j])
		new[i++] = value[j++];
	if (j < len)
		len = j;
	rest_of_str = start + len;
	while (cmd[rest_of_str])
		new[i++] = cmd[rest_of_str++];
	free(cmd);
	cmd = new;
	return (new);
}

char	*find_value(t_shell *ms, char *key)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = ft_strlen(key);
	while (ms->envp[i])
	{
		if (!ft_strncmp(key, ms->envp[i], ft_strlen(key))
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
		{
			value = (ft_strchr(ms->envp[i], '=') + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char	*find_key_in_envp(t_shell *ms, char *key)
{
	int	i;

	i = 0;
	while (i < ms->envp_size)
	{
		if (!key_exists(ms, key))
			i++;
		else if (key_exists(ms, key))
			return (key);
	}
	return (NULL);
}
