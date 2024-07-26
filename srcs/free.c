/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:34 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/26 11:02:42 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_single(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

void	free_double(char **arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
		free_single(arr[i++]);
	free(arr);
	arr = NULL;
}


void free_node(t_process_node **lst)
{
	t_process_node *temp;
	
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->command != NULL)//char **cmd;
			free_double((*lst)->command);
		if ((*lst)->node_line != NULL)//char	*input;
			free_single((*lst)->node_line);
		if ((*lst)->redirect_in != NULL)//char **cmd;
			free_double((*lst)->redirect_in );
		if ((*lst)->redirect_out != NULL)//char **cmd;
			free_double((*lst)->redirect_out);
		if ((*lst)->here_doc != NULL)//char	*input;
			free_single((*lst)->here_doc);
		if ((*lst)->append_s != NULL)//char	*input;
			free_single((*lst)->append_s);
		if ((*lst)->cmd_path != NULL)//char	*input;
			free_single((*lst)->cmd_path);
		
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

int free_env(t_shell *ms)
{
	
	// if (!ms->envp_paths)
	// 	return ;
	if (ms->envp)
	{	
		free_double(ms->envp);	
	}
	if (ms->cwd)
		free_single(ms->cwd);
	//may need to free old pwd
	return (-1);
}

void free_shell(t_shell *ms)//free ms
{
	if (!ms->envp_paths)
		return ;
	else
		free_double(ms->envp_paths);
	// if (ms->line)
	// 	free(ms->line);
	// if (ms->pids)
	// 	free(ms->pids);
	
}

//close_and_free
int close_and_free(t_shell *ms)
{
	close(ms->fd[0]);
	close(ms->fd[1]);
	close(ms->read_end);
	free_shell(ms);
	free_env(ms);
	return (-1);
}
