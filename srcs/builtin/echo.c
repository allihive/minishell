/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:35:43 by alli              #+#    #+#             */
/*   Updated: 2024/06/24 19:29:21 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_value(t_shell *ms, char *str)
// {
	
// }

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

void	echo(t_shell *ms, char **output)
{
	int	i;
	int	j;
	// int	k;
	char *value;
	int	len;
	int	value_len;

	i = 0;
	j = 0;
	while (output[i])
	{
		i++;
		if (output[i][0] == '-')
		{
			if (ft_charncmp(output[i]))
			{
				if (ft_strchr(output[i], '$'))
				{
					// k = 1;
					len = ft_strlen(output[i - 1]);
					if (!ft_strncmp(ft_substr(output[i], 1, len), ms->envp[j], len))
					{
						value_len = ft_strlen(ms->envp[i]);
						value = ft_substr(ms->envp[j], len + 1, value_len); //len+1 get rid of the equal sign
						if (!value)
							return ; //error_handle
						printf("printf value: %s\n", value);
						ft_putstr_fd(value, 1);
					}
					j++;
				}
				ft_putstr_fd(output[i], 1);
				i++;
			}
		}
		else
		{
			if (ft_strchr(output[i], '$'))
			{
				// k = 1;
				len = ft_strlen(output[i - 1]);
				if (!ft_strncmp(ft_substr(output[i], 1, len), ms->envp[j], len))
				{
					value_len = ft_strlen(ms->envp[i]);
					value = ft_substr(ms->envp[j], len + 1, value_len - len); //len+1 get rid of the equal sign
					if (!value)
						return ; //error_handle
					printf("printf value: %s\n", value);
					ft_putstr_fd(value, 1);
				}
				j++;
			}
			else
			{
				ft_putstr_fd(output[i], 1);
				ft_putchar('\n');
				i++;
			}
		}
	}
}
