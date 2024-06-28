/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:58:46 by alli              #+#    #+#             */
/*   Updated: 2024/06/27 19:16:03 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *ms, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[i + 1] != NULL)
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd("numeric arguments required\n", 1);
		ms->excode = 1;
		exit(1);//free_exit(); pipe exit and cleann up
	}
	//figure out exit number 
	if (count_cmd(ms->list) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);// free_exit(); pipe exit
	}
}