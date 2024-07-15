/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:58:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/15 10:14:28 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_is_digit(char *cmd)
{
	int	i;
	// int	j;

	i = 0;
	printf("cmd  in cmd_is_digit %s\n", cmd);
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		return (ft_atoi(cmd));
	else //(ft_isdigit(cmd[i]) == 0)
			return (0);
	
}

void	ft_exit(t_shell *ms, char **cmd)
{
	int	i;

	i = 0;// cannot have more than 1 argv only exit 1234
	printf("cmd_is_digit(cmd[1]): %d\n", cmd_is_digit(cmd[1]));
	if (!ft_strncmp(cmd[0], "exit", 4) && cmd_counter(cmd) == 2 && cmd_is_digit((cmd[1])))
	{
		ft_putstr_fd("exit\n", 1);
		exit(ms->excode % 256);
	}
	else if (cmd_counter(cmd) > 2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd("too many arguments", 1);
		exit (2);
	}
	else if (!cmd_is_digit(cmd[1]))
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd("numeric arguments required\n", 1);
		ms->excode = 2;
		exit(2);//free_exit(); pipe exit and cleann up
	}
	//figure out exit number 
	// if (count_cmd(ms->list) == 1)
	// {
	// 	// free_exit(); pipe exit
	// }
	// exit(ex_code % 256);
}