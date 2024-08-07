/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:40:11 by alli              #+#    #+#             */
/*   Updated: 2024/07/31 13:18:09 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


_Bool	check_case(char *cmd, char *builtin)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != builtin[i] && cmd[i] + 32 != builtin[i])
			return (0);
		i++;
	}
	if (cmd[i] != builtin[i])
		return (0);
	return (1);
}


_Bool	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strncmp(cmd, "export\0", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset\0", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit\0", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd\0", 3) == 0)
		return (1);
	if (cmd[0] == 'p' || cmd[0] == 'P')
		return (check_case(cmd, "pwd\0"));//check both small or capitalized letters
	if (cmd[0] == 'e' || cmd[0] == 'E')
	{
		if (check_case(cmd, "env\0")
			|| check_case(cmd, "echo\0"))
			return (1);
	}
	return (0);
}


int	call_builtin(t_shell *ms, t_process_node *node)
{
	//printf("ms->excode before in call builtin %d\n", ms->excode);
	if (ft_strncmp(node->command[0], "export", 6) == 0)
		ft_export(ms, node->command, 1); //added 1 for fd
	else if (ft_strncmp(node->command[0], "unset", 5) == 0)
		unset(ms, node->command);
	else if(ft_strncmp(node->command[0], "exit", 4) == 0)
	{
		printf("goes into ft_exit\n");
		ft_exit(ms, node->command);
		// printf("ms->excode in call builtin after func %d\n", ms->excode);
	}
	else if (ft_strncmp(node->command[0], "pwd", 3) == 0)
		pwd(ms, 0,  ms->fd[1]);
	else if (ft_strncmp(node->command[0], "env", 3) == 0)
		env(ms, ms->fd[1]);
	else if (ft_strncmp(node->command[0], "echo", 4) == 0)
		echo(ms, node->command, ms->fd[1]);
    else if (ft_strncmp(node->command[0], "cd", 2) == 0)
		cd(ms, node->command, 0, 0);
	return (ms->excode);
}
