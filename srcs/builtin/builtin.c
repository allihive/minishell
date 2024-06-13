/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:23:17 by alli              #+#    #+#             */
/*   Updated: 2024/06/13 10:35:28 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ascii_order(t_shell *ms, char letter)
{
	int		i;
	int		j;
	char **tmp;

	i = -1;
	tmp = ms->envp;
	while (++i < ms->envp_size)
	{
		j = -1;
		if (tmp[i][0] == letter)
		{
			ft_putstr_fd("declare -x ", 1);
			while (tmp[i][++j] != '=' && tmp[i][j] != '\0')
				ft_putchar_fd(tmp[i][j], 1);
			if (tmp[i][j] == '=')
			{
				ft_putstr_fd("=\"", 1);
				while (tmp[i][++j])
					ft_putchar_fd(tmp[i][j], 1);
				ft_putstr_fd("\"\n", 1);
			}
		}
	}
}

void	envp_print(t_shell *ms)
{
	char	**new_list;
	int		i;
	int		j;
	int 	letter;

	i = 0;
	j = 0;
	letter = ' ';
	new_list = ft_calloc(ms->envp_size + 1, sizeof(char *));
	if (!new_list)
		return ;//some sort of error exit here
	while (i < ms->envp_size)
	{
		if (ms->envp[i][j] == '_' || ms->envp[i][j + 1] == '=')
			i++;
		while (letter < 127)
		{
			print_ascii_order(ms, letter);
			letter++;
		}
		i++;
	}
}

void	execute_builtin(t_shell *ms)
{
	if (ft_strncmp(ms->line, "export", 6) == 0)
		export(ms, 0);
	else if (ft_strncmp(ms->line, "pwd", 3) == 0)
		pwd(ms, 0);
	else if (ft_strncmp(ms->line, "env", 3) == 0)
		env(ms);
	// else if (ft_strncmp(ms->line, "unset", 5) == 0)
	// 	unset(ms);
}
