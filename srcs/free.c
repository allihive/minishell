/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:34 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/02 18:08:47 by yhsu             ###   ########.fr       */
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

	i = 0;
	dprintf(2, "1 in free double\n");
	
	while (arr[i])
	{
		if(arr[i])
			free(arr[i++]);
	}
	free(arr);
	arr = NULL;
	dprintf(2, "2 in free double\n");
}
static void free_node_content(t_process_node *node)
{
	if (node->command)
		free_double(node->command);
	if (node->node_line != NULL)//char	*input;
		free_single(node->node_line);
	if (node->redirect_in != NULL)//char **cmd;
		free_double(node->redirect_in );
	if (node->redirect_out != NULL)//char **cmd;
		free_double(node->redirect_out);
	if (node->here_doc != NULL)//char	*input;
		free(node->here_doc);
	if (node->append_s != NULL)//char	*input;
		free_double(node->append_s);
	if (node->cmd_path != NULL)//char	*input;
		free_single(node->cmd_path);
	node->here_doc = NULL;
}

void free_node(t_process_node **process)
{
	t_process_node *temp;
	
	if (process == NULL || *process == NULL)
		return ;
	while ((*process)->next != NULL)
	{
		temp = *process;
		*process = (*process)->next;
		free_node_content(temp);
	}
	free_node_content(*process);
	*process = NULL;
	
	// while (*lst)
	// {
	// 	temp = (*lst)->next;
	// 	if ((*lst)->command != NULL)//char **cmd;
	// 		free_double((*lst)->command);
	// 	if ((*lst)->node_line != NULL)//char	*input;
	// 		free_single((*lst)->node_line);
	// 	if ((*lst)->redirect_in != NULL)//char **cmd;
	// 		free_double((*lst)->redirect_in );
	// 	if ((*lst)->redirect_out != NULL)//char **cmd;
	// 		free_double((*lst)->redirect_out);
	// 	if ((*lst)->here_doc != NULL)//char	*input;
	// 		free_single((*lst)->here_doc);
	// 	if ((*lst)->append_s != NULL)//char	*input;
	// 		free_double((*lst)->append_s);
	// 	if ((*lst)->cmd_path != NULL)//char	*input;
	// 		free_single((*lst)->cmd_path);
		
	// 	free(*lst);
	// 	*lst = temp;
	// }
	//*lst = NULL;
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
	if (ms->line)
		free_single(ms->line);
	if (!ms->pids)
		return ;
	else
		free(ms->pids);
	ms->pids = NULL;
	
}

//close_and_free
int close_and_free(t_shell *ms)
{
	close(ms->fd[0]);
	close(ms->fd[1]);
	close(ms->read_end);

	free_node(&ms->list);
	
	free_shell(ms);
	free_env(ms);
	exit (ms->excode);
	return (-1);
}
