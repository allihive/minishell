/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:56:47 by alli              #+#    #+#             */
/*   Updated: 2024/08/09 14:22:55 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_update(t_shell *ms, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (name[len] != '=')
		len++;
	while (ms->envp[i])
	{
		if (ft_strncmp(ms->envp[i], name, len) == 0 && ms->envp[i][len] == '=')
			break ;
		i++;
	}
	if (ms->envp[i][len] == '=')
	{
		free(ms->envp[i]);
		ms->envp[i] = name;
		if (!ms->envp[i])
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
			return (NULL);
		free(name);
		return (new_str);
	}
	new_str = ft_strjoin(name, "=");
	if (!new_str)
		return (NULL);
	free(name);
	return (new_str);
}

void	envp_add(t_shell *ms, char *name)
{
	char	**new;
	int		i;

	i = 0;
	ms->envp_size += 1;
	ms->flag = 0;
	if (!name)
		close_and_free(ms);
	new = ft_calloc((ms->envp_size + 1), sizeof(char *));
	if (!new)
		close_and_free(ms);
	while (i < ms->envp_size - 1 && ms->envp[i])
	{
		new[i] = ms->envp[i];
		i++;
	}
	new [i] = "\0";
	if (name && !ms->flag)
		new[i] = latest_envp(name);
	free(ms->envp);
	ms->envp = new;
}

void	update_or_add_envp(t_shell *ms, char **cmd, int j, int flag)
{
	char	*current_cmd;

	current_cmd = ft_strdup(cmd[j]);
	if (!current_cmd)
	{
		free(cmd[j]);
		return ;
	}
	if (name_exists_env(ms, cmd[j]))
		envp_update(ms, current_cmd);
	if (name_exists_env(ms, cmd[j]) == NULL)
		envp_add(ms, current_cmd);
	if (flag == 0)
		ms->excode = 0;
}

int	ft_export(t_shell *ms, char **cmd, int fd)
{
	int	i;
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
		if (export_str_check(cmd[j]) && ms->envp[i])
		{
			error_msg(cmd[0], cmd[j], "not a valid identifier", ms->excode = 1);
			flag = 1;
		}
		if (!export_str_check(cmd[j]) && ms->envp[i])
			update_or_add_envp(ms, cmd, j, flag);
		j++;
	}
	return (ms->excode);
}
