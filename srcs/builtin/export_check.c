/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:55:13 by alli              #+#    #+#             */
/*   Updated: 2024/08/09 11:16:22 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_exists_env(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	key = ft_substr(name, 0, i + 1);
	if (!key)
		return (NULL);
	len = ft_strlen(key + 1);
	i = 0;
	while (i < ms->envp_size && ms->envp[i])
	{
		if ((ft_strncmp(key, ms->envp[i], len) == 0)
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
		{
			free(key);
			return (ms->envp[i] + len);
		}
		i++;
	}
	free(key);
	return (NULL);
}

char	*env_exists(char *name, t_shell *ms)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		close_and_free(ms);
	len = ft_strlen(tmp);
	while (ms->envp[i] && !ft_strnstr(ms->envp[i], tmp, len))
		i++;
	if (ms->envp[i] != NULL)
	{
		free(tmp);
		return (ms->envp[i] + len);
	}
	free(tmp);
	return (NULL);
}

int	export_str_check(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i] && str[i] != '='
		&& (ft_isalnum(str[i]) || str[i] == '_'))
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
