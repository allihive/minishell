/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@hive.student.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/05/31 15:52:42 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//error_handle();

/* return 1 if char c is a spaces */
int ifisspace(char c)
{
		if (c == 32 || (c <= 9 && c >= 13))
			return (1);	
	return (0);
}

int check_syntax(t_shell *ms);// mutiple pipe ... back slash, : export > ( syntax error near unexpected token `newline')
{
	
	
	
	
	return (0);
}

char *point_end(char *line)
{
    while (*line && *line != '|' && *line != '\"' && *line != '\'')
        line++;
	if (*line == '\"' || *line == '\'')
	{
		line++;
		while(*line && *line != '|' && *line != '\"' && *line != '\'')
			line++;
		return(line);
	}
    
    return(line);
}



int init_process_node(char *line, t_shell *ms)
{
	t_process_node *new;
	char *temp;
	
	if (!line || !*line || check_syntax(ms->line) || ifisspace(line))
		return (false);
	while (*line)
	{
		
		while (ifisspae(*line))
			line++;
		
		//make temp point to the end of the
		temp = point_end(line); 
		
		
		//calloc for new 
		new = ft_calloc(1, sizeof(t_process_node));
		// if (!new)
		// 	error_handle();
		new->fd_in = -1;
		new->fd_out = -1;
		if (new->node_line)
			new->node_line = ft_substr(line, 0, (temp - line));
		if (!new->node_line )
			free(new->node_line )
			
	}
	 
	
}


static void execute_shell(t_shell *ms)
{
	parse_process_node(&ms->node, ms); //oritginal:parse_modules(&ms->mods, ms)
	//execute_children(ms);
	//wait_children(ms);
}