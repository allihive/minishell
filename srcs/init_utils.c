/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:59:14 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/31 11:04:48 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char check_delimiter(char *line)
{
	char *single_quote;
	char *double_quote;

	single_quote = ft_strchr(line, '\'');
	double_quote = ft_strchr(line, '\"');
	if (!single_quote && !double_quote)
		return (0);
	else if ((single_quote && double_quote) && (single_quote > double_quote))
		return ('\"');
	else if (single_quote && double_quote)
		return ('\'');
	else if (double_quote)
		return ('\"');
	else 
		return ('\'');
}
	
int invalid_redirect( char *line, char redirect)
{
	while(*line)
	{
		if (*line == '$' || (*line != redirect && !ifismeta(*line)))
			line++;
		else if (ifismeta(*line))// ' '' : 
		{
			line++;
			while (*line && *line != '\'' && *line != '\"')//echo "Hello World"
				line++;
			line++;//skip ' or "
		}
		else
		{
			line++;
			if (*line == redirect)
				line++;
			if (ifisspace(*line))
				line++;
			if (!*line || *line == '<' || *line == '>')
				return (1);//fail
		}
	}
	return (0);
}

int count_cmd(t_process_node *list)
{
	int n;
	
	n = 0;
	while (list)
	{
		//dprintf(2,"list->node_line;%s\n", list->node_line );
		list = list->next;
		n++;
	}
	return (n);	
}

char *point_end(char *line)
{
    while (*line)
    {
        while (*line && *line != PIPE && *line != DOUBLEQUOTE && *line != SINGLEQUOTE)
          line++;
        if (*line == DOUBLEQUOTE || *line == SINGLEQUOTE)
        {
            line++;
            while(*line && *line != DOUBLEQUOTE && *line != SINGLEQUOTE)
            	line++;
            line++;
        }
        else
          return(line);
        
    }
    return(line);
}

int empty_prompt(char *input)
{
	while (ifisspace(*input))
		input++;
	if (!*input)
		return (1);//true
	return (0);//false
}
