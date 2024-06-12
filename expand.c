/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@hive.student.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:37:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/06/12 17:08:40 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_the_shit_out(char *cmd, t_process_node *mod, t_shell *ms)
{
	char *env;
	int i;
	
	dprintf(2 ,"this line: %s need to be expand\n", cmd);
	i = 0;
	//expand the variable
	while (cmd[i])
	{
		if (*cmd == SINGLEQUOTE)
			mod->sinquote = i;
		else if (*cmd == DOUBLEQUOTE)
			mod->doublequote = i;
		else
			i++;
		if (cmd[i] == '$')
			
		
		i++;
	}

	
	//delete quote
	
}
