/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:50:23 by alli              #+#    #+#             */
/*   Updated: 2024/08/06 13:13:44 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t global_signal = 0;

void	init_envp(t_shell *ms, char **envp)
{
	int i;
	// char **new;
	ms->envp_size = 0;
	while (envp[ms->envp_size])
		ms->envp_size++;
	ms->envp = ft_calloc(ms->envp_size + 1, sizeof(char *));
	if (!ms->envp)
		error_handle(ms);
	i = 0;
	while (i < ms->envp_size)
	{
		// printf("initialized shell1\n");
		ms->envp[i] = ft_strdup(envp[i]);
		// printf("ms->envp = %s\n", ms->envp[i]);
		if (!ms->envp[i])
			error_handle(ms);
		i++;
	}
	// ms->envp[ms->envp_size] = NULL;
	// return (ms->envp);
}

int add_shlvl(t_shell *ms)//create the export function
{
	int shlvl;
	char *shlvl_str;
	char *tmp;
	
	shlvl_str = getenv("SHLVL");
	if (shlvl_str == NULL || shlvl_str[0] == '\0')
		envp_add(ms, ft_strdup("SHLVL=1"));
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		envp_update(ms, ft_strdup("SHLVL=0"));
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str)
		return (1);// should be an error here
	tmp = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!tmp)
	{
		free(shlvl_str);
		error_handle(ms);	
	}
	envp_update(ms, tmp);
	// free(tmp);
	return (shlvl);
}




void	initialize_shell(t_shell *ms, char **envp)
{
	ft_memset(ms, 0, sizeof(*ms));
	init_envp(ms, envp);
	add_shlvl(ms);
	// free_env(ms);
	// return;
	//know the pwd somehow
}



void execute_shell(t_shell *ms)
{
	
	parse_process_node(&ms->list, ms); //oritginal:parse_modules(&ms->mods, ms)
	// printf("&ms->list == ms ? %d\n", &ms->list == ms->list);
	if (!ms->list)
	{
		printf("!ms->list\n");
		exit(free_env(ms));
	}
	else if (pipex(ms->list, ms) == -1)
	{
		printf("pipex(ms->list, ms) == -1\n");
		exit(ms->excode);
	}
	//printf("execute_shell::END\n");
}
void	quit(t_shell *ms)
{
	ft_putstr_fd("exit\n", 2);
	
	//free_env(ms);
	close_and_free(ms);
	//free(ms->list->command);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell ms;
	(void)argv;

	if (argc == 1)
	{
		initialize_shell(&ms, envp);
		while (true)
		{
			set_signal();
			ms.line = readline("lobster-shell 🦞: ");
			if (!ms.line)
			{
				dprintf(2,"in !ms.line\n");
				//error_handle(&ms);
				quit(&ms);
			}
			else if (ms.line[0] != 0)
				add_history(ms.line);
			if (init_process_node(ms.line, &ms) == 0)
			{
				execute_shell(&ms);
								
				//int j = 0;
				// while (ms.list->command[j])
				// {
					
				// 	dprintf(1, "command[%d]: %s\n", j, ms.list->command[j]);
				// 	j++;
				// }	
				free_node(&ms.list);
				free_shell(&ms);
				
			}
			// if (ms.envp)
			// 	free_env(&ms);
		}
		close_and_free(&ms);
		rl_clear_history();
		return (ms.excode);
	}
}


