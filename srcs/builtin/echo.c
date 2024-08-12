/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:35:43 by alli              #+#    #+#             */
/*   Updated: 2024/08/09 18:11:24 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_charncmp(char *str)
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

void	echo(t_shell *ms, char **output, int fd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (output[i])
	{
		while (ft_charncmp(output[i]))
		{
			if (output[i + 1] == NULL)
				return ;
			j = 1;
			i++;
		}
		if (!j)
			j = 0;
		ft_putstr_fd(output[i], fd);
		if (output[i + 1] == NULL && j == 0)
			ft_putchar_fd('\n', fd);
		else if (output[i + 1] != NULL)
			ft_putchar_fd(' ', fd);
		i++;
	}
	ms->excode = 0;
}
