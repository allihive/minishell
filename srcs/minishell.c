/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:50:23 by alli              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/25 15:22:29 by yhsu             ###   ########.fr       */
=======
/*   Updated: 2024/07/06 21:22:17 by yhsu             ###   ########.fr       */
>>>>>>> parent of 60c5e28 (added free_shell and free_env)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(t_shell *ms, char **envp)
{
	int i;
	
	ms->envp_size = 0;
	while (envp[ms->envp_size])
		ms->envp_size++;
	ms->envp = ft_calloc(ms->envp_size + 1, sizeof(char *));
	if (!ms->envp)
		error_handle(ms);
	i = 0;
	while (i < ms->envp_size)
	{
		ms->envp[i] = ft_strdup(envp[i]);
		// printf("ms->envp = %s\n", ms->envp[i]);
		if (!ms->envp[i])
			error_handle(ms);
		i++;
	}
}

int add_shlvl(t_shell *ms)//create the export function
{
	int shlvl;
	char *shlvl_str;
	
	// shlvl = 0;
	shlvl_str = getenv("SHLVL");
	if (shlvl_str == NULL || shlvl_str[0] == '\0')
		envp_add(ms, ft_strdup(("SHLVL=1")));
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		envp_update(ms, ft_strdup(("SHLVL=0")));
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str)
		return (1);// should be an error here
	shlvl_str = ft_strjoin("SHLVL=", shlvl_str);
	if (!shlvl_str)
		error_handle(ms);
	envp_update(ms, shlvl_str);
	// printf("shlvl: %d\n", shlvl);
	// printf("before exiting %s\n", shlvl_str);
	free(shlvl_str);
	return (shlvl);
}

void	initialize_shell(t_shell *ms, char **envp)
{
	ft_bzero(ms, sizeof(*ms));
	init_envp(ms, envp);
	add_shlvl(ms);
	//know the pwd somehow
}

/*
int	main(int argc, char **argv, char **envp)
{
	t_shell ms;
	(void)argv;
	// (void)argc;

	if (argc == 1)
	{
		initialize_shell(&ms, envp);
		while (true)
		{
			set_signal();
			ms.line = readline("lobster-shell 🦞: ");
			//add_history(ms.line);
			if (!ms.line)
				error_handle(&ms);
			else if (ms.line[0] != 0)
			{
				add_history(ms.line);
			}
			if (init_process_node(ms.line, &ms) == 0)
			{
				//execute_shell(&ms);
				//printf("main0\n");
				parse_process_node(&ms.list,&ms);
				
				//printf("main1\n");
				if (!ms.list)
					exit(free_env(&ms));
				else if (pipex(ms.list, &ms) == -1)
					exit(ms.excode);
			}
			//printf("main2\n");
			free_shell(&ms);
			free_node(&ms.list);
		}
		return (ms.excode);
	}
}
*/

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
				error_handle(&ms);
			// else if (ms.line[0] != '\0')
			// {
			// 	add_history(ms.line);
			// 	init_process_node(ms.line, &ms);
			// 	execute_shell(&ms);
			// 	//execute_builtin(&ms, ms.list);
			// }
			else if (ms.line[0] != 0)
			{
				add_history(ms.line);
			}
			if (init_process_node(ms.line, &ms) == 0)
			{
				//execute_shell(&ms);
				//printf("main0\n");
				parse_process_node(&ms.list,&ms);
				
				//printf("main1\n");
				if (!ms.list)
					exit(free_env(&ms));
				else if (pipex(ms.list, &ms) == -1)
					exit(ms.excode);
				
				free_shell(&ms);
				free_node(&ms.list);
			
			}
			


			
			
		}
		return (ms.excode);
	}
}


