/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:50:24 by alli              #+#    #+#             */
/*   Updated: 2024/05/30 14:50:44 by alli             ###   ########.fr       */
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
int check_shlvl(t_shell *ms)
{
	int shlvl;
	char *shlvl_str;
	
	shlvl_str = getenv(shlvl);
	shlvl = ft_atoi(shlvl_str);
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str || shlvl_str[i] = '\0')
		return (export(ms, ft_strdup("SHLVL=1")));
	if (shlvl < 0)
		return (export(ms, ft_strdup("SHLVL=0")));
	shlvl = export(ms, ft_strjoin("SHLVL=", shlvl_str));
	if (!shlvl)
}

void	initialize_shell(t_shell *ms, char **envp)
{
	ft_bzero(ms, sizeof(*ms));
	init_envp(ms, envp);
	check_shlvl(ms);
	//check shell level (increment if necessary)
	//know the pwd somehow
}

int	main(int argc, char **argv, char **envp)
{
	t_shell ms;
	(void)argv;
	(void)argc;

	initialize_shell(&ms, envp);
	while (true)
	{
		set_signal();
		ms.line = readline("lobster-shell 🦞: ");
		if (!ms.line)
			error_handle(&ms);
		else if (ms.line[0] != '\0')
			add_history(ms.line);
		//split and execute shell here
	}
	return (0);
}

