/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:34 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 10:10:56 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_process_node **lst)
{
	t_process_node	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->command)
			free_lst_cmd(lst);
		if ((*lst)->node_line != NULL)
			free_single(&(*lst)->node_line);
		if ((*lst)->redirect_in != NULL)
			free_double((*lst)->redirect_in);
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

int	free_env(t_shell *ms)
{
	if (ms->envp != NULL)
		free_double(ms->envp);
	if (ms->cwd)
		free_single(&ms->cwd);
	return (-1);
}

void	free_shell(t_shell *ms)
{
	if (ms->envp_paths)
		free_double(ms->envp_paths);
	if (ms->line)
		free_single(&ms->line);
	if (!ms->pids)
		return ;
	else
		free(ms->pids);
	ms->pids = NULL;
}

int	close_and_free(t_shell *ms)
{
	close(ms->fd[0]);
	close(ms->fd[1]);
	if (!(ms->read_end == -1))
		close(ms->read_end);
	free_node(&ms->list);
	if (ms->envp)
		free_env(ms);
	free_shell(ms);
	exit(ms->excode);
	return (-1);
}
