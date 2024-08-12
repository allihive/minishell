/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:50:23 by alli              #+#    #+#             */
/*   Updated: 2024/08/12 11:06:41 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_global_signal = 0;

int	init_envp(t_shell *ms, char **envp)
{
	int	i;

	ms->envp_size = 0;
	while (envp[ms->envp_size])
		ms->envp_size++;
	ms->envp = ft_calloc(ms->envp_size + 1, sizeof(char *));
	if (!ms->envp)
		error_handle(ms, 0);
	i = 0;
	while (i < ms->envp_size)
	{
		ms->envp[i] = ft_strdup(envp[i]);
		if (!ms->envp[i])
		{
			free_env(ms);
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_shlvl(t_shell *ms)
{
	int		shlvl;
	char	*shlvl_str;
	char	*tmp;

	shlvl_str = getenv("SHLVL");
	if (shlvl_str == NULL || shlvl_str[0] == '\0')
		envp_add(ms, ft_strdup("SHLVL=1"));
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		envp_update(ms, ft_strdup("SHLVL=0"));
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str)
		return (1);
	tmp = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!tmp)
		free_env(ms);
	envp_update(ms, tmp);
	return (shlvl);
}

void	initialize_shell(t_shell *ms, char **envp)
{
	ft_memset(ms, 0, sizeof(*ms));
	if (init_envp(ms, envp) == 1)
		return ;
	add_shlvl(ms);
}

void	execute_shell(t_shell *ms)
{
	parse_process_node(&ms->list, ms);
	if (!ms->list)
		exit(free_env(ms));
	else if (pipex(ms->list, ms) == -1)
		exit(ms->excode);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	ms;

	(void)argv;
	if (argc == 1)
	{
		initialize_shell(&ms, envp);
		while (TRUE)
		{
			set_signal();
			ms.line = readline("lobster-shell 🦞: ");
			if (!ms.line)
				quit(&ms);
			else if (ms.line[0] != 0)
				add_history(ms.line);
			if (init_process_node(ms.line, &ms) == 0)
			{
				execute_shell(&ms);
				free_node(&ms.list);
				free_shell(&ms);
			}
			
		}
		return (ms.excode);
	}
}
