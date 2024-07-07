/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:35:43 by alli              #+#    #+#             */
/*   Updated: 2024/07/07 21:41:57 by yhsu             ###   ########.fr       */
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

void	echo(t_shell *ms, char **output) //char **output
{
	int	i;
	int	j;
	// int	k;

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
		ft_putstr_fd(output[i], 1);
		if (output[i + 1] == NULL && j == 0)
			ft_putchar_fd('\n', 1);
		else if(output[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	
	ms->excode = 0;
}



