/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:23:17 by alli              #+#    #+#             */
/*   Updated: 2024/06/11 11:44:20 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	print_ascii_order(t_shell *ms, char letter)
{
	int		j;
	char	**tmp;

	j = ' ';
	tmp = ms->envp;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(ms->envp[i], 1);// or print the single variable of the sorted list
	ft_putstr_fd("\n", 1);
}

void	envp_print(t_shell *ms)
{
	char	**new_list;
	int		i;
	int		j;
	char 	*letter;

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
		if (letter < 127)
		{
			print_ascii_order(ms, letter);
			// ft_putstr_fd("declare -x ", 1);
			// ft_putstr_fd(ms->envp[i], 1);// or print the single variable of the sorted list
			// ft_putstr_fd("\n", 1);
			letter++;
		}
		i++;
	}
}

void	execute_builtin(t_shell *ms)
{
	if (ft_strncmp(ms->line, "export", 6) == 0)
		export(ms, 0);
}