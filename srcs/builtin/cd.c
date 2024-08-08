/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:15:21 by alli              #+#    #+#             */
// /*   Updated: 2024/07/31 15:31:59 by alli             ###   ########.fr       */
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

void	cd(t_shell *ms, char **cmd, char *pwd, char *oldpwd)
{
	char	cwd[1000];
	
	if (getcwd(cwd, 1000) == NULL)
		return ;
	if (cmd[1] == NULL)
	{
		char *home;
		char *home_value;
		home = env_exists("HOME", ms);
		if (!home)
		{
			error_msg(cmd[0], 0, "HOME not set", 1, ms);
			return ;//don't exit remain in shell
		}
		home_value = find_value(ms, "HOME");
		if (chdir(home_value) == 0)
			set_pwd(ms, pwd, oldpwd, cwd);
		else if(chdir(home_value) != 0)
		{
			error_msg(cmd[0], home_value, "No such file or directory", 1, ms);
			return ;
		}
	}
	else if (cmd[1] && chdir(cmd[1]) == 0)
		set_pwd(ms, pwd, oldpwd, cwd);
}
