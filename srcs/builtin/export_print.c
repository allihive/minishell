/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:23:17 by alli              #+#    #+#             */
/*   Updated: 2024/08/09 09:28:10 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	write_env(char *str, int fd)
{
	int	j;

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
	char	**tmp;

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
	int	i;
	int	j;
	int	letter;

	i = 0;
	j = 0;
	letter = ' ';
	while (i < ms->envp_size && ms->envp[i])
	{
		if (ms->envp[i][j] == '_' || ms->envp[i][j + 1] == '=')
			i++;
		while (letter < 127)
		{
			print_ascii_order(ms, letter, fd);
			letter++;
		}
		i++;
	}
}
