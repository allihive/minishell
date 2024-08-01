/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:58:46 by alli              #+#    #+#             */
/*   Updated: 2024/08/01 09:48:28 by alli             ###   ########.fr       */
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
void	exit_shell(t_shell *ms, char **cmd)
{
	if(!cmd_is_digit(cmd[1]) && cmd_counter(cmd) > 2)
	{
		error_msg(cmd[0], 0, "too many arguments", 2, ms);
		close_and_free(ms);
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
		close_and_free(ms);
	}
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
			exit_shell(ms, cmd);
	}
	else if (!cmd_is_digit(cmd[1]) && ft_atoi(cmd[1]) == 0)
		exit_shell(ms, cmd);
	else if (!ft_strncmp(cmd[0], "exit", 4) && cmd_counter(cmd) == 2 && cmd_is_digit((cmd[1])))
		exit_shell(ms, cmd);
	return (0);
}
