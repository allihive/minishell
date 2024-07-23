/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:45:25 by alli              #+#    #+#             */
/*   Updated: 2024/07/19 11:42:13 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handle(t_shell *ms)
{
	if (ms->envp)
	{
		ft_free_strs(ms->envp, 0, 0);
		// free(ms);
		if (ms->line)
			free(ms->line);
		exit(ms->excode);
	}
	ft_printf("Readline unable to read");
	exit(ms->excode);
}

// void	free_everything(t_shell *ms, t_process_node *node)
// {
// 	if 
// }

// void	error_command(t_shell *ms, t_process_node *node)
// {
// 	// ft_putstr_fd("%s: command not found", node->command[0]);
// 	ms->excode = 1;
// 	//should free everything and exit
// 	// free_everything(ms, node);
// 	return (ms->excode);
// }






void	only_print_error(char *name)
{
	if (ft_putstr_fd("lobster-shell 🦞: ", 2) == -1)
	{
		perror("pipex: write error");
		exit(1);
	}
	perror(name);
	exit(1);
}