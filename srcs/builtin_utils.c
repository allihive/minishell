/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:40:11 by alli              #+#    #+#             */
/*   Updated: 2024/07/26 10:40:12 by alli             ###   ########.fr       */
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
