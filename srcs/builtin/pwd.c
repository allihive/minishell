/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:25:55 by alli              #+#    #+#             */
/*   Updated: 2024/08/08 16:20:49 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
