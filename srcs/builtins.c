/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:56:47 by alli              #+#    #+#             */
/*   Updated: 2024/05/31 15:39:31 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char env_exists(char *name, t_shell *ms)
{
	char	*tmp;
	int		len;
	int 	i;
	
	i = 0;
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		error_handle(ms);
	len = ft_strlen(tmp);
	while (ms->envp[i] && !ft_substr(ms->envp[i], tmp, len))
		i++;
	if (ms->envp[i] != NULL)
		return (ms->envp[i] + len);
	return (NULL);
}

int	export(t_shell *ms, char *cmd)
{
	if (!cmd)
		return (1);
	if (!export_str_check(cmd))
	{
		env_exists(ms, cmd);
	}
	//check to see if command is null
	//not null -> error check?
		// check if the name exists and check the string/content
		//update
		//if the name_exists and doesn't have anything
			//add envp
}

int	export_str_check(char *str)
{
	int i;
	
	i = 0;
	if (str[i] == ft_isdigit(str[i]))
		return (1);
	while (str[++i] && str[i] != "="  && (ft_isalnum(str[i]) || str[i] == "_"))
		;
	if (str[i] == '\0')
		return (0);
	else 
		return (1);
}
