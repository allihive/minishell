/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:25:55 by alli              #+#    #+#             */
/*   Updated: 2024/06/12 10:29:16 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(t_shell *ms, char **cmd) //will be a child built in
{
	(void)cmd;
	char	*pwd_path;
	pwd_path = getcwd(NULL, 0);
	
	if (!pwd_path)
		error_handle(ms);
	ms->cwd = pwd_path;
	ft_putstr_fd(ms->cwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd_path);
}