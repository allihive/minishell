/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:35:43 by alli              #+#    #+#             */
/*   Updated: 2024/07/31 12:13:53 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int ft_charncmp(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
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
static int	empty_echo(char *str, int fd)
{
	int j;

	j = 0;
	if (!str)
	{
		ft_putchar_fd(' ', fd);
		if (j == 0)
			ft_putchar_fd('\n', fd);
	}
	return (j);
}

void	echo(t_shell *ms, char **output, int fd) //char **output
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (!output[i])
		j = empty_echo(output[i], fd);
	while (output[i])
	{
		while (ft_charncmp(output[i]))
		{
			j = 1;
			i++;
		}
		if (!j)
			j = 0;
		ft_putstr_fd(output[i], fd);
		if (output[i + 1] == NULL && j == 0)
			ft_putchar_fd('\n', fd);
		else if(output[i + 1] != NULL)
			ft_putchar_fd(' ', fd);
		i++;
	}
	ms->excode  = 0;
}

