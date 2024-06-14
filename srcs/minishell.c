/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:50:23 by alli              #+#    #+#             */
/*   Updated: 2024/06/13 15:58:28 by alli             ###   ########.fr       */
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

int check_shlvl(t_shell *ms)//create the export function
{
	int shlvl;
	char *shlvl_str;
	
	// shlvl = 0;
	shlvl_str = getenv("SHLVL");
	if (shlvl_str == NULL || shlvl_str[0] == '\0')
		// return (export(ms, &ft_strdup("SHLVL=1")));
		envp_add(ms, ft_strdup(("SHLVL=1")));
	shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		// return (export(ms, &ft_strdup("SHLVL=0")));
		envp_update(ms, ft_strdup(("SHLVL=0")));
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str)
		return (1);// should be an error here
	shlvl_str = ft_strjoin("SHLVL=", shlvl_str);
	if (!shlvl_str)
		error_handle(ms);
	envp_update(ms, shlvl_str);
	free(shlvl_str);
	return (shlvl);
}

void	initialize_shell(t_shell *ms, char **envp)
{
	ft_bzero(ms, sizeof(*ms));
	init_envp(ms, envp);
	check_shlvl(ms);
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
		// set_signal();
		ms.line = readline("lobster-shell 🦞: ");
		if (!ms.line)
			error_handle(&ms);
		else if (ms.line[0] != '\0')
		{
			add_history(ms.line);
			init_process_node(ms.line, &ms);
			execute_shell(&ms);
			execute_builtin(&ms, ms.list);
		}
		// split and execute shell here
		// ms.line = readline("lobster-shell 🦞: ");
		// if (!ms.line)
		// 	error_handle(&ms);
		// else
		// {
		// 	add_history(ms.line);
		// 	free(ms.line);
		// }
		// //--------------
		// //---------------
	}
	return (0);
	
}

// int main()// for parse test
// {
// 	t_shell ms;
	
	
// 	char s[30] = "echo hello $USER ";
// 	//char s[500] = "echo 'hello $USER' >> infile | cat < outfile.txt < outfile";
// 	//char s[34] = "cat 42 < outfile.txt < outfile ";
// 	ms.line = s;
// 	init_process_node(ms.line, &ms);
// 	execute_shell(&ms);
// }