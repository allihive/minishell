/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:58:46 by alli              #+#    #+#             */
/*   Updated: 2024/08/05 17:38:17 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_is_digit(char *cmd)
{
	int	i;
	
	i = 0;
	if (!cmd)
	{
		return (0);
	}
	if (ft_atoi(cmd) == 0)
		return (0);
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		return (ft_atoi(cmd));
	else
			return (0);
	
}

int	ft_exit(t_shell *ms, char **cmd)
{
	if ((!cmd[1] || !ft_strncmp(cmd[1], "0", 1)))
	{
		ft_putstr_fd("exit\n", 1);
		ms->excode = 0;
		close_and_free(ms);
	}
	else if (cmd_counter(cmd) > 2)
	{
		if (cmd_is_digit(cmd[1]))
		{
			error_msg(cmd[0], 0, "too many arguments", 1, ms);
			return (ms->excode = 1);
		}
		else
		{
			error_msg(cmd[0], 0, "too many arguments", 2, ms);
			close_and_free(ms);
		}
	}
	else if (!cmd_is_digit(cmd[1]) && ft_atoi(cmd[1]) == 0)
	{
		error_msg(cmd[0], cmd[1], "numeric arguments required", 2, ms);
		close_and_free(ms);
	}
	else if (!ft_strncmp(cmd[0], "exit", 4) && cmd_counter(cmd) == 2 && cmd_is_digit((cmd[1])))
	{
		ft_putstr_fd("exit\n", 1);
		ms->excode = ft_atoi(cmd[1]) % 256;
		
		int j = 0;
		while (ms->list->command[j])
		{
			
			dprintf(1, "command[%d]: %s\n", j, ms->list->command[j]);
			j++;
		}
		ft_putstr_fd("exit::before calling close_and_free(ms)\n", 1);		
		close_and_free(ms);
	}
	return (0);
}
