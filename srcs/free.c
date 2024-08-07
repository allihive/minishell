/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:34 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/08 14:30:28 by yhsu             ###   ########.fr       */
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
	// dprintf(2, "1 in free double\n\n");
	
	while (arr[i])
	{
		//dprintf(2, "free double arr[%d]:%s\n", i, arr[i]);		
		free(arr[i++]);
	}
	free(arr);
	
	// arr = NULL;
	//dprintf(2, "2 in free double\n");
}
// static void free_node_content(t_process_node *node)
// {
// 	if (node->command)
// 	{
// 		dprintf(2,"node->command\n");
// 		free_double(node->command);
// 	}	
// 	if (node->node_line != NULL)//char	*input;
// 		free_single(node->node_line);
// 	if (node->redirect_in != NULL)//char **cmd;
// 		free_double(node->redirect_in );
// 	if (node->redirect_out != NULL)//char **cmd;
// 		free_double(node->redirect_out);
// 	if (node->here_doc != NULL)//char	*input;
// 		free(node->here_doc);
// 	if (node->append_s != NULL)//char	*input;
// 		free_double(node->append_s);
// 	if (node->cmd_path != NULL)//char	*input;
// 		free_single(node->cmd_path);
// 	node->here_doc = NULL;
// }

void free_node(t_process_node **lst)
{
	t_process_node *temp;
	
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->command)
		{
			//printf("entered free node\n");
			free_double((*lst)->command);
			(*lst)->command = NULL;
		}
		

		if ((*lst)->node_line != NULL)//char	*input;
			free_single(&(*lst)->node_line);
		if ((*lst)->redirect_in != NULL)//char **cmd;
			free_double((*lst)->redirect_in );
		if ((*lst)->redirect_out != NULL)//char **cmd;
		{
			// int i = 0;
			
			// while ((*lst)->redirect_out[i])
			// {
			// 	dprintf(2, "free node redirect_out[%d]: %s\n", i, (*lst)->redirect_out[i]);
			// 	i++;
			// }
			free_double((*lst)->redirect_out);
		}
		if ((*lst)->here_doc != NULL)//char	*input;
			free_single(&(*lst)->here_doc);
		if ((*lst)->append_s != NULL)//char	*input;
			free_double((*lst)->append_s);
		if ((*lst)->cmd_path != NULL)//char	*input;
			free_single(&(*lst)->cmd_path);
		
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

int free_env(t_shell *ms)
{
	
	// if (!ms->envp_paths)
	// 	return ;
	if (ms->envp != NULL)
	{	
		// printf("in free env\n");
		free_double(ms->envp);	
	}
	if (ms->cwd)
		free_single(&ms->cwd);
	//may need to free old pwd
	return (-1);
}

void free_shell(t_shell *ms)//free ms
{
	// if (!ms->envp_paths)
	// 	return ;
	// else
	// 	free_double(ms->envp_paths);

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

// //close_and_free
// int close_and_free(t_shell *ms)
// {
// 	close(ms->fd[0]);
// 	close(ms->fd[1]);
// 	close(ms->read_end);


// 	free_node(&ms->list);
// 	if (ms->envp)
// 		free_env(ms);
// 	free_shell(ms);
// 	exit (ms->excode);
// 	return (-1);
// }

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
	if      (ms->read_end >= 0)
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
