/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:23:17 by alli              #+#    #+#             */
/*   Updated: 2024/07/31 14:57:22 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void write_env(char *str,  int fd)
{
	int j;
	
	j = 0;
	ft_putstr_fd("declare -x ", fd);
	while (str[j] != '=' && str[j] != '\0')
	{
		ft_putchar_fd(str[j], fd);
		j++;
	}
	if (str[j] == '=')
	{
		j++;
		ft_putstr_fd("=\"", fd);
		while (str[j])
		{
			ft_putchar_fd(str[j], fd);
			j++;
		}
	ft_putstr_fd("\"\n", fd);
	}
}

static void	print_ascii_order(t_shell *ms, char letter, int fd)
{
	int		i;
	char **tmp;

	i = 0;
	tmp = ms->envp;
	if (!tmp)
		return ;
	while (i < ms->envp_size)
	{
		if (tmp[i] && tmp[i][0] == letter)
			write_env(tmp[i], fd);
		i++;
	}
}


void	envp_print(t_shell *ms, int fd)
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
	while (i < ms->envp_size && ms->envp[i])
	{
		if (ms->envp[i][j] == '_' || ms->envp[i][j + 1] == '=')
			i++;
		while (letter < 127)
		{
			// printf("entered print ascii order\n");
			print_ascii_order(ms, letter, fd);
			letter++;
		}
		i++;
	}
}

void	execute_builtin(t_shell *ms, t_process_node *node)
{
	if (ft_strncmp(node->command[0], "export", 6) == 0)
	{
		ft_export(ms, node->command, 1);
	}
	else if (ft_strncmp(node->command[0], "pwd", 3) == 0)
		pwd(ms, 0, 1);
	else if (ft_strncmp(node->command[0], "env", 3) == 0)
		env(ms, 1);
	else if (ft_strncmp(node->command[0], "unset", 5) == 0)
		unset(ms, node->command);
	else if(ft_strncmp(node->command[0], "echo", 4) == 0)
		echo(ms, node->command, 1);
	else if(ft_strncmp(node->command[0], "exit", 4) == 0)
		ft_exit(ms, node->command);
	else if (ft_strncmp(node->command[0], "cd", 2) == 0)
		cd(ms, node->command, 0, 0);
}
