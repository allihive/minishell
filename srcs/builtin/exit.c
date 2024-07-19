/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:10:49 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/19 18:10:53 by yhsu             ###   ########.fr       */
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