/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:34 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/08 16:07:26 by yhsu             ###   ########.fr       */
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

void free_node(t_process_node **lst)
{
	t_process_node *temp;
	
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->command)
		{
			free_double((*lst)->command);
			(*lst)->command = NULL;
		}
		if ((*lst)->node_line != NULL)
			free_single(&(*lst)->node_line);
		if ((*lst)->redirect_in != NULL)
			free_double((*lst)->redirect_in );
		if ((*lst)->redirect_out != NULL)
			free_double((*lst)->redirect_out);
		if ((*lst)->here_doc != NULL)
			free_single(&(*lst)->here_doc);
		if ((*lst)->append_s != NULL)
			free_double((*lst)->append_s);
		if ((*lst)->cmd_path != NULL)
			free_single(&(*lst)->cmd_path);
		
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

int free_env(t_shell *ms)
{
	if (ms->envp != NULL)
	{	
		free_double(ms->envp);	
	}
	if (ms->cwd)
		free_single(&ms->cwd);
	return (-1);
}

void free_shell(t_shell *ms)//free ms
{
	if (ms->envp_paths)
	{
		// printf("in free shell\n");
		free_double(ms->envp_paths);
	}
	
	if (ms->line)
		free_single(&ms->line);
	if (!ms->pids)
		return ;
	else
		free(ms->pids);
	ms->pids = NULL;
	
}

int close_and_free(t_shell *ms)
{
	if (ms->fd[0] >= 0)
	{
		close(ms->fd[0]);
		ms->fd[0] = -1;
	}
	if (ms->fd[1] >= 0)
	{
		close(ms->fd[1]);
		ms->fd[1] = -1;
	}
	if (ms->read_end >= 0)
	{
		close(ms->read_end);
		ms->read_end = -1;
	}
	free_node(&ms->list);
	if (ms->envp)
			free_env(ms);
	free_shell(ms);
	exit (ms->excode);
	return (-1);
}
