/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@hive.student.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:50:24 by alli              #+#    #+#             */
/*   Updated: 2024/05/29 12:59:10 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(t_shell *ms, char **envp)
{
	int i;
	
	while (envp[ms->envp_size])
		ms->envp_size++;
	ms->envp = ft_calloc(ms->envp_size, sizeof(ms->envp));
	if (!ms->envp)
		error_handle(ms);
	i = 0;
	while (i < ms->envp_size)
	{
		ms->envp[i] = ft_strdup(envp[i]);
		if (!ms->envp[i])
			error_handle(ms);
		i++;
	}
}
//copy environment parameters function

void	initialize_shell(t_shell *ms, char **envp)
{
	ft_bzero(ms, sizeof(*ms));
	init_envp(ms, envp);
	//initialize the environment
	//check shell level (increment if necessary)
	//know the pwd somehow
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_shell ms;

	initialize_shell(&ms, envp);
	while (true)
	{
		line = readline("lobster-shell 🦞: ");
		if (!line)
			error_handle(&ms);
		else
		{
			add_history(line);
			free(line);
		}
	}
	return (0);
	
}
