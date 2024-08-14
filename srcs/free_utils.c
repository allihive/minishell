/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:48:11 by alli              #+#    #+#             */
/*   Updated: 2024/08/14 11:23:06 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_single(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

void	free_double(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{	
		free(arr[i++]);
	}
	free(arr);
}

void	free_lst_cmd(t_process_node **lst)
{
	free_double((*lst)->command);
	(*lst)->command = NULL;
}

void	error_handle(t_shell *ms, char *line)
{
	if (line)
		free (line);
	free_node(&ms->list);
	if (ms->envp)
		free_env(ms);
	exit(ms->excode);
}
