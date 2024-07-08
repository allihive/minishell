/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:15:21 by alli              #+#    #+#             */
/*   Updated: 2024/06/29 19:47:33 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_shell *ms, char **cmd, char *pwd, char *oldpwd)
{
	char *cwd;

	printf("cmd[1]: %s\n", cmd[1]);
	cwd = getcwd(NULL, 0);//getting current working directory
	if (!cwd)
	{
		return ;
	}
	printf("chdir(cmd[1]): %d\n", chdir(cmd[1]));
	if (cmd[1] && chdir(cmd[1]) == 0) //checks if there's ../../ or Documents/minishell
	{
		printf("env_exists %s\n", env_exists("PWD", ms));
		if (env_exists("PWD", ms)) //if PWD exists (make it the OLDPWD)
		{
			oldpwd = ft_strjoin("OLDPWD=", find_value(ms, "PWD"));// make the string for OLDPWD
			if (!oldpwd)
				return ; //error_handle
			printf("oldpwd set: %s\n", oldpwd);
		}
		if (!pwd) //have PWD pointer emtpy and join it with the string
		{
			pwd = ft_strjoin("PWD=", getcwd(cwd, 1000)); //create the string
			if (!pwd)
				return ; //error handle here? 
		}
		envp_update(ms, pwd);
		envp_update(ms, oldpwd);
	}
	else if (!cmd[1]) // checks if it's just cd
	{
		char *home;
		char *home_value;
		
		home = env_exists("HOME", ms);
		home_value = find_value(ms, "HOME");
		if (!home)
		{
			ft_putstr_fd("bash: cd: HOME not set", 2);
			ms->exit_code = 1;
			return ;//don't exit remain in shell
		}
		if (chdir(home_value) == 0)
		{
			chdir(find_value(ms, "HOME"));
			if (env_exists(pwd, ms))
			{
				oldpwd = ft_strjoin("OLDPWD=", find_value(ms, pwd));
				if (!oldpwd)
					return ;
			}
			pwd = ft_strjoin("PWD=", getcwd(cwd, 1000));
			if (!pwd)
				return ;
			
			envp_update(ms, pwd);
			envp_update(ms, oldpwd);
		}
		else if(chdir(home_value) != 0) //home has something that is not correct
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(home_value, 2);
			ft_putstr_fd(": No such file or directory", 2);
			ms->exit_code = 1;
			return ;
		}
	}
}

/*some error functiion tests*/
//ln -s /path/that/does/not/exist broken_link -> bash: cd: broken_link: No such file or directory
//cd /path/that/does/not/exist ->bash: cd: /path/that/does/not/exist: No such file or directory

//unset HOME -> bash: cd: HOME not set
//export HOME=<invalid location> -> bash: cd: str value: No such file or directory
//