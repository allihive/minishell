/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:40:11 by alli              #+#    #+#             */
/*   Updated: 2024/08/14 10:09:57 by yhsu             ###   ########.fr       */
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
	if (ft_strncmp(cmd, "echo\0", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd\0", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env\0", 4) == 0)
		return (1);
	return (0);
}

int	call_builtin(t_shell *ms, t_process_node *node)
{
	if (ft_strncmp(node->command[0], "export", 6) == 0)
		ft_export(ms, node->command, 1);
	else if (ft_strncmp(node->command[0], "unset", 5) == 0)
		unset(ms, node->command);
	else if (ft_strncmp(node->command[0], "exit", 4) == 0)
		ft_exit(ms, node->command);
	else if (ft_strncmp(node->command[0], "pwd", 3) == 0)
		pwd(ms, 0, ms->fd[1]);
	else if (ft_strncmp(node->command[0], "env", 3) == 0)
		env(ms, ms->fd[1]);
	else if (ft_strncmp(node->command[0], "echo", 4) == 0)
		echo(ms, node->command, ms->fd[1]);
	else if (ft_strncmp(node->command[0], "cd", 2) == 0)
		cd(ms, node->command, 0, 0);
	return (ms->excode);
}
