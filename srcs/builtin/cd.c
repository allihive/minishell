/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:15:21 by alli              #+#    #+#             */
/*   Updated: 2024/08/09 14:23:26 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_shell *ms, char *pwd, char *oldpwd, char *cwd)
{
	if (env_exists("PWD", ms))
	{
		oldpwd = ft_strjoin("OLDPWD=", find_value(ms, "PWD"));
		if (!oldpwd)
		{
			ms->excode = 1;
			return ;
		}
	}
	pwd = ft_strjoin("PWD=", getcwd(cwd, 1000));
	if (!pwd)
	{
		ms->excode = 1;
		return ;
	}
	envp_update(ms, pwd);
	envp_update(ms, oldpwd);
}

void	to_home(t_shell *ms, char *cwd, char *pwd, char *oldpwd)
{
	char	*home;
	char	*value;

	home = env_exists("HOME", ms);
	if (!home)
	{
		error_msg("cd", 0, "HOME not set", ms->excode = 1);
		return ;
	}
	value = find_value(ms, "HOME");
	if (chdir(value) == 0)
		set_pwd(ms, pwd, oldpwd, cwd);
	else if (chdir(value) != 0)
	{
		error_msg("cd", value, "No such file or directory", ms->excode = 1);
		return ;
	}
}

void	cd(t_shell *ms, char **cmd, char *pwd, char *oldpwd)
{
	char	cwd[1000];
	int		cmds;

	cmds = cmd_counter(cmd);
	if (cmds > 2)
	{
		error_msg(cmd[0], 0, "too many arguments", ms->excode = 1);
		return ;
	}
	if (getcwd(cwd, 1000) == NULL)
		return ;
	if (cmd[1] == NULL)
		to_home(ms, cwd, pwd, oldpwd);
	else if (cmd[1] && chdir(cmd[1]) == 0)
		set_pwd(ms, pwd, oldpwd, cwd);
	else if (cmd[1] && chdir(cmd[1]) != 0)
	{
		error_msg(cmd[0], cmd[1], "No such file or directory", ms->excode = 1);
		return ;
	}
}
