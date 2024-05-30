/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@hive.student.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/05/30 19:14:12 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
/* return 1 if char c is a spaces */
int ifisspace(char c)
{
		if (c == 32 || (c <= 9 && c >= 13))
			return (1);	
	return (0);
}

int check_syntax(t_shell *ms);// mutiple pipe ... back slash, : export > ( syntax error near unexpected token `newline')
{
	
}

int init_process_node(char *line, t_shell *ms)
{
	if (!line || !*line || check_syntax(ms->line) || ifisspace(line))
		return (false);
}


static void execute_shell(t_shell *ms)
{
	parse_process_node(&ms->mods, ms); //oritginal:parse_modules(&ms->mods, ms)
	//execute_children(ms);
	//wait_children(ms);
}