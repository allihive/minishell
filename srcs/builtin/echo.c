/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:35:43 by alli              #+#    #+#             */
/*   Updated: 2024/07/24 11:28:57 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int ft_charncmp(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	echo(t_shell *ms, char **output, int fd) //char **output
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i++; // skip echo

	while (output[i] && ft_charncmp(output[i]))
	{
		i++;
		j = 1;
	}
	while (output[i])
	{
		ft_putstr_fd(output[i], fd);
		if (output[i + 1] == NULL && j == 0)
			ft_putchar_fd('\n', fd);
		else if(output[i + 1] != NULL)
			ft_putchar_fd(' ', fd);
		i++;
	}
	ms->excode  = 0;
}

