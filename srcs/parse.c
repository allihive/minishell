/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 13:58:53 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_process_node(t_process_node **list, t_process_node *new)
{
	t_process_node	*last_node;

	if (!list || !new)
		return ;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		last_node = *list;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new;
	}
}

char	*no_quote(char *cmd)
{
	char	*result;
	int		new_len;
	int		i;
	int		j;

	j = 0;
	while (ifisspace(cmd[j]))
		j++;
	new_len = ft_strlen(cmd + j) - 1;
	result = malloc(sizeof(char) * new_len);
	if (result == NULL)
		ft_putstr_fd("malloc error", 2);
	i = 0;
	while (i < new_len - 1)
	{
		result[i] = cmd[j + 1];
		i++;
		j++;
	}
	result[i] = '\0';
	free(cmd);
	return (result);
}

void	check_dollar(char **command, t_process_node *mod, t_shell *ms)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = command;
	dprintf(2, "in check dollar\n");
	while (command[i])
	{
		j = 0;
		dprintf(2, "1 in check dollar command[i]:%s\n", command[i]);
		while (command[i][j])
		{
			//dprintf(2, "command[i][j]:%c\n", command[i][j]);
			if (command[i][j] == '$' )
			{
				if (command[i][j + 1] == '\0')
					break;
				command[i] = expand_it_out(tmp[i], mod, ms);	
			}	
			j++;
		}
		command[i] = quote_remover(command[i]);
		dprintf(2, "2 in check dollar command[i]:%s\n", command[i]);
		i++;
	}
}


int redirect_not_in_quote(char c, char *input, int k, t_shell *ms)// if redirect is not in quote return 0 
{
	int quote = -1;
	int l = 0;
	char * tmp;
	
	//dprintf(2, "c:%c, input:%s , j:%d, k: %d\n", c, input, j, k);
	if (c == '<' || c == '>')
	{
		// while (k >= 0)
		// {
			
			tmp = ft_substr(input, 0, k);
			//dprintf(2, "tmp:%s\n", tmp);
			//dprintf(2, "tmp[l]:%c\n", tmp[l]);
			while (tmp[l])
			{
				if (tmp[l] == DOUBLEQUOTE  && quote == -1)
					quote = DOUBLEQUOTE;
				else if (tmp[l] == DOUBLEQUOTE  && quote == DOUBLEQUOTE)
					quote = -1;
				else if(tmp[l] == SINGLEQUOTE  && quote == -1)
					quote = SINGLEQUOTE;
				else if (tmp[l] == SINGLEQUOTE  && quote == SINGLEQUOTE)
					quote = -1;
				l++;
			}
			free (tmp);
			if (quote != -1)
				return (0);
			else
			{
				ms->execute = -1;
				return (1);
			} 
			
		// 	k--;
		// }
		
	}
	else
		return (0);
}

void	parse_mod(char *input, t_process_node *mod, t_shell *ms)
{
	char	*command;
	char	*start;
	//int quote = -1;
	//int i = 0;
	
	start = input;
	//dprintf(2, "input:%s\n", input);
	
	//dprintf(2, "i:%d\n", i);
	while (*start && redirect_not_in_quote(*start, input, start - input, ms) == 0)
	{
		start++;
		//i++;
	}
	
	
	
	command = ft_substr(input, 0, (start - input));
	
	mod->command = get_cmd_arr(command, ms);
	free(command);

	
	if (is_builtin(mod->command[0]))
		mod->builtin = 1;


	int a = 0;
	
	while (mod->command[a])
	{
		dprintf(2, "1 mod->command[%d]:%s\n",a, mod->command[a]);
		a++;
	}

	
	check_dollar(mod->command, mod, ms);

	while (mod->command[a])
	{
		dprintf(2, "2 mod->command[%d]:%s\n",a, mod->command[a]);
		a++;
	}
}

void	parse_process_node(t_process_node **list, t_shell *ms)
{
	t_process_node	*mod;
	char			*input;

	mod = *list;
	while (mod)
	{
		input = mod->node_line;
		parse_mod(input, mod, ms);
		mod = mod->next;
	}
}
