/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:23:17 by alli              #+#    #+#             */
/*   Updated: 2024/06/19 14:56:50 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ascii_order(t_shell *ms, char letter)
{
	int		i;
	int		j;
	char **tmp;

	i = 0;
	tmp = ms->envp;
	if (!tmp)
		return ;
	while (i < ms->envp_size)
	{
		j = 0;
		if (tmp[i] && tmp[i][0] == letter)
		{
			printf("tmp[i][0]: %c\n", tmp[i][0]);
			ft_putstr_fd("declare -x ", 1);
			while (tmp[i][j] != '=' && tmp[i][j] != '\0')
			{
				ft_putchar_fd(tmp[i][j], 1);
				j++;
			}
			if (tmp[i][j] == '=')
			{
				ft_putstr_fd("=\"", 1);
				while (tmp[i][j])
				{
					ft_putchar_fd(tmp[i][j], 1);
					j++;
				}
				ft_putstr_fd("\"\n", 1);
			}
			j++;
		}
		i++;
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

void	execute_builtin(t_shell *ms, t_process_node *node)
{
	if (ft_strncmp(node->command[0], "export", 6) == 0)
		ft_export(ms, node->command);
	else if (ft_strncmp(node->command[0], "pwd", 3) == 0)
		pwd(ms, 0);
	else if (ft_strncmp(node->command[0], "env", 3) == 0)
		env(ms);
	else if (ft_strncmp(ms->line, "unset", 5) == 0)
		unset(ms, node->command);
}
