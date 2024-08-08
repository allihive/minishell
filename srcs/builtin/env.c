/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:59:34 by alli              #+#    #+#             */
/*   Updated: 2024/08/08 08:06:17 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env(t_shell *ms, int fd)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ms->envp;
	while (*tmp && i < ms->envp_size)
	{
		ft_putstr_fd(tmp[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}
