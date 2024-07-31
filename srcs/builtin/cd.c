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

// void	set_pwd(t_shell *ms, char *pwd, char *oldpwd, char *cwd)
// {
// 	if (env_exists("PWD", ms))
// 	{
// 		oldpwd = ft_strjoin("OLDPWD=", find_value(ms, "PWD"));
// 		if (!oldpwd)
// 		{
// 			printf("malloc failed\n");
// 			return ;
// 		}
// 	}
// 	pwd = ft_strjoin("PWD=", getcwd(cwd, 1000));
// 	if (!pwd)
// 		return ;
// 	envp_update(ms, pwd);
// 	envp_update(ms, oldpwd);
// }

void	cd(t_shell *ms, char **cmd, char *pwd, char *oldpwd)
{
	char cwd[1000];
	
	if (getcwd(cwd, 1000) == NULL)//getting current working directory
	{
		printf("getcwd failed\n");
		return ;
	}
	if (cmd[1] == NULL) // checks if it's just cd
	{
		//ms->excode = cd_home(ms, env_exists("HOME", ms), find_value(ms, "HOME"));
		char *home;
		char *home_value;
		
		home = env_exists("HOME", ms);
		if (!home)
		{
			ft_putstr_fd("bash: cd: HOME not set", 2);
			ms->excode = 1;
			return ;//don't exit remain in shell
		}
		// printf("pwd: %s\n", pwd);
		// printf("env_exists: %s\n", env_exists(pwd, ms));
		home_value = find_value(ms, "HOME");
		if (chdir(home_value) == 0)
		{
			// set_pwd(ms, pwd, oldpwd, cwd);
			printf("chdir(home value) entered\n");
			if (env_exists("PWD", ms))
			{
				oldpwd = ft_strjoin("OLDPWD=", find_value(ms, "PWD"));
				if (!oldpwd)
					return ;
			}
			// printf("oldpwd: %s\n", oldpwd);
			pwd = ft_strjoin("PWD=", getcwd(cwd, 1000));
			if (!pwd)
				return ;
			// printf("new pwd: %s\n", pwd);
			envp_update(ms, pwd);
			envp_update(ms, oldpwd);
		}
		else if(chdir(home_value) != 0) //home has something that is not correct
		{
			error_msg(cmd[0], home_value, "No such file or directory");
			ms->excode = 1;
			return ;
		}
	}

	else if (cmd[1] && chdir(cmd[1]) == 0) //checks if there's ../../ or Documents/minishell
	{
		printf("env_exists %s\n", env_exists("PWD", ms));
		if (env_exists("PWD", ms)) //if PWD exists (make it the OLDPWD)
		{
			oldpwd = ft_strjoin("OLDPWD=", find_value(ms, "PWD"));// make the string for OLDPWD
			if (!oldpwd)
				return ; //error_handle
			printf("oldpwd set: %s\n", oldpwd);
		}
		// if (!pwd) //have PWD pointer emtpy and join it with the string
	
			// dprintf(2, "cwd: %s\n", gcwd);
		pwd = ft_strjoin("PWD=", getcwd(cwd, 1000)); //create the string
		if (!pwd)
			return ; //error handle here? 
		printf("pwd: %s\n", pwd);
		printf("oldpwd %s\n", oldpwd);
		envp_update(ms, pwd);
		envp_update(ms, oldpwd);
		// set_pwd(ms, pwd, oldpwd, cwd);
		printf("finished updating\n");
	}
}


/*some error functiion tests*/
//ln -s /path/that/does/not/exist broken_link -> bash: cd: broken_link: No such file or directory
//cd /path/that/does/not/exist ->bash: cd: /path/that/does/not/exist: No such file or directory

//unset HOME -> bash: cd: HOME not set
//export HOME=<invalid location> -> bash: cd: str value: No such file or directory
//