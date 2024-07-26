/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:45:25 by alli              #+#    #+#             */
/*   Updated: 2024/07/26 10:40:22 by alli             ###   ########.fr       */
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

void	error_msg(char *cmd, char *str, char *msg)
{
	if (!ft_strncmp(cmd, "export", 6))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		if (str)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
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
	if (ft_putstr_fd("lobster-shell 🦞: in only print error", 2) == -1)
	{
		perror("pipex: write error");
		exit(1);
	}
	perror(name);
	exit(1);
}