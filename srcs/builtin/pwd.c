/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:25:55 by alli              #+#    #+#             */
/*   Updated: 2024/07/09 11:53:11 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	pwd(t_shell *ms, char **cmd) //will be a child built in
// {
// 	(void)cmd;
// 	char	*pwd_path;
// 	pwd_path = getcwd(NULL, 0);
	
// 	if (!pwd_path)
// 		error_handle(ms);
// 	ms->cwd = pwd_path;
// 	ft_putstr_fd(ms->cwd, 1);
// 	ft_putchar_fd('\n', 1);
// 	free(pwd_path);
// }
void	pwd(t_shell *ms, char **cmd, int fd)
{
	char	*str;
	char	buf[1000];
	
	(void)cmd;

	str = getcwd(buf, 1000);
	if (str)
	{
		ft_putendl_fd(str, fd);
		ms->excode = 0;
	}
	else
		ft_putendl_fd(ms->cwd, fd);
}