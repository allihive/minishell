/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:58:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/26 09:45:29 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_is_digit(char *cmd)
{
	int	i;
	// int	j;

	i = 0;
	// printf("cmd in cmd_is_digit %s\n", cmd);
	if (!cmd)
	{
		return (0);
	}
	// printf("goes into atoi");
	if (ft_atoi(cmd) == 0)
		return (0);
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		return (ft_atoi(cmd));
	else //(ft_isdigit(cmd[i]) == 0)
			return (0);
	
}

int	ft_exit(t_shell *ms, char **cmd)
{
	int	i;

	i = 0;
	// printf("cmd_is_digit(cmd[1]): %d\n", ft_atoi(cmd[1]));
	// printf("cmd[0]: %s\n", cmd[0]);
	// printf("cmd[1]: %s\n", cmd[1]);
	if ((!cmd[1] || !ft_strncmp(cmd[1], "0", 1)))
	{
		ms->excode = 0;
		printf("exit code in ft-exit %d\n", ms->excode);
		return (ms->excode);
	}
	else if (cmd_counter(cmd) > 2)
	{
		if (cmd_is_digit(cmd[1]))
		{
			ms->excode = 1;
			//stays in shell
		}
		else
		{
			ms->excode = 2;
			//exits shell
		}
		error_msg(cmd[0], 0, "too many arguments");
		return(ms->excode);
	}
	else if (!cmd_is_digit(cmd[1]) && ft_atoi(cmd[1]) == 0)
	{
		error_msg(cmd[0], cmd[1], "numeric arguments required");
		ms->excode = 2;
		//exited shell
		return(ms->excode);
		// exit(2);//free_exit(); pipe exit and cleann up
	}
	else if (!ft_strncmp(cmd[0], "exit", 4) && cmd_counter(cmd) == 2 && cmd_is_digit((cmd[1])))
	{
		ft_putstr_fd("exit\n", 1);
		ms->excode = ft_atoi(cmd[1]) % 256;
		return(ms->excode);
	}
	return (0);
}
