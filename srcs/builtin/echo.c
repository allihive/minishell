/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:35:43 by alli              #+#    #+#             */
/*   Updated: 2024/06/24 20:06:16 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *name_exists(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	while(name[i] && name[i] != '=')
		i++;
	key = ft_substr(name, 0, i + 1);
	if (!key)
		return (NULL); //should be error_handle
	len = ft_strlen(key + 1);
	i = 0;
	while (i < ms->envp_size && ms->envp[i])
	{
		if ((ft_strncmp(key, ms->envp[i], len) == 0) 
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
				return (ms->envp[i] + len);
		i++;
	}
	return (NULL);
}

void	print_value(t_shell *ms, char *str)
{
	char *key;
	int	len;
	char *value;
	int	value_len;
	int	i;

	i = 0;
	len = ft_strlen(str) - 1;
	key = ft_substr(str, 1, len);//USER without $
	if (!key)
		return ;//error handle
	while (i < ms->envp_size && ms->envp[i])
	{
		if (name_exists(ms, key))
		{
			value_len = ft_strlen(ms->envp[i]);
			value = ft_substr(ms->envp[i], len + 1, value_len); //len+1 get rid of the equal sign
			if (!value)
				return ; //error_handle
			printf("printf value: %s\n", value);
			ft_putstr_fd(value, 1);
		}
	}
}

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
	// int	j;
	// int	k;

	i = 1;
	// j = 0;
	while (output[i])
	{
		printf("output %s\n", output[i]);
		if (output[i][0] == '-')
		{
			if (ft_charncmp(output[i]))
			{
				if (ft_strchr(output[i], '$'))
				{
					// k = 1;
					print_value(ms, output[i]);
					// j++;
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
				// len = ft_strlen(output[i - 1]);
				// if (!ft_strncmp(ft_substr(output[i], 1, len), ms->envp[j], len))
				// {
				// 	value_len = ft_strlen(ms->envp[i]);
				// 	value = ft_substr(ms->envp[j], len + 1, value_len - len); //len+1 get rid of the equal sign
				// 	if (!value)
				// 		return ; //error_handle
				// 	printf("printf value: %s\n", value);
				// 	ft_putstr_fd(value, 1);
				print_value(ms, output[i]);
				// 
				// j++;
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


