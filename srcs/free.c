/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:34 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/06 20:49:06 by yhsu             ###   ########.fr       */
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


//free_env(ms)

//close_and_free