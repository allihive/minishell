/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:45:25 by alli              #+#    #+#             */
/*   Updated: 2024/07/23 17:28:46 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handle(t_shell *ms)
{
	if (!ms->envp)//hsu added for <infile
		return ;
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






void	only_print_error(char *name)
{
	if (ft_putstr_fd("lobster-shell 🦞: in only print error", 2) == -1)
	{
		perror("pipex: write error");
		exit(1);
	}
	perror(name);
	exit(1);
}