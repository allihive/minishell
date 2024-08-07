/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/07 13:38:56 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void append_process_node(t_process_node **list, t_process_node *new)
{
	t_process_node *last_node;
	
	if (!list || !new)
		return ;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		
		
		last_node = *list;
		
		while(last_node->next)
			last_node = last_node->next;
		last_node->next = new;
	}
	
}



//char	*no_quote(char *cmd, t_process_node *mod) //for get_cmd_arr
char	*no_quote(char *cmd)//for test
{
	char	*result;
	int		new_len;
	int		i,j;
	
	j = 0;
	while (ifisspace(cmd[j]))
		j++;
	new_len = ft_strlen(cmd + j) - 1;//7
	result = malloc(sizeof(char) * new_len);
	if (result == NULL)
		ft_putstr_fd("malloc error", 2);// need change to print_error
	i = 0;
	while (i < new_len - 1)
	{
		result[i] = cmd[j+1];
		i++;
		j++;
	}
	result[i] = '\0';
	free(cmd);
	return (result);
}




void check_dollor(char **command, t_process_node *mod, t_shell *ms)
{
	int i, j;
	i = 0;
	char **tmp;

	tmp = command;
	while (command[i])//'hello $USER' "$'HOME'"
	{
		j = 0;
		while (command[i][j])
		{
			if (command[i][j] == '$' )
			{
				dprintf(2,"after expand it out command[i]: %s\n", command[i]);
				command[i] = expand_it_out(tmp[i], mod, ms);
				//dprintf(2,"after expand it out command[i]: %s\n", command[i]);
				//if (command[i][j + 1] == '$');
					
			}	
			j++;
		}
		command[i] = quote_remover(command[i]);
		i++;
	}
}

void parse_mod(char *input, t_process_node *mod, t_shell *ms)//echo "hello $USER" > infile.txt 
{
	char *command;//input without redirection
	char *start;// check the first redirect for cmd
	
	start = input;
	while (*start && !ifisredirect(*start))//input  變成 echo "hello $USER"
		start++;
		
	command = ft_substr( input, 0 , (start - input));		
	//get rid of ' '' save back to the string ; change mode
	mod->command = get_cmd_arr(command, ms); //get (cmd[0]echo cmd[1]"hello $USER" or cmd[0]echo cmd[1]hello cmd[2]$USR)
	free(command);
	
	// int p = 0;
	// while (mod->command[p])
	// {
	// 	dprintf(2, "mod->command[%d]:%s\n", p, mod->command[p]);
	// 	p++;
	// }
	
	if (is_builtin(mod->command[0]))
		mod->builtin = 1;
	check_dollor(mod->command, mod, ms);
}


//dive line by '|' and save them in linked list
void parse_process_node(t_process_node **list, t_shell *ms)
{
	t_process_node *mod;//command node
	char *input;

	mod = *list;	
	while (mod)
	{
		// if (mod->next)
		// 	input = mod->next->node_line;
		// else
		// 	input = mod->node_line;
		input = mod->node_line;
		parse_mod(input, mod, ms);//for parse test
		mod = mod->next;
		dprintf(2, "end of parse process\n");
	}
	
}
