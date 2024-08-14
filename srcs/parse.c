/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 12:44:51 by alli             ###   ########.fr       */
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
	while (command[i])
	{
		j = 0;
		while (command[i][j])
		{
			if (command[i][j] == '$')
			{
				if (command[i][j + 1] == '\0')
					break ;
				command[i] = expand_it_out(tmp[i], mod, ms);
			}	
			j++;
		}
		command[i] = quote_remover(command[i]);
		i++;
	}
}

void	parse_mod(char *input, t_process_node *mod, t_shell *ms)
{
	char	*command;
	char	*start;
	int		a;

	start = input;
	while (*start && redirect_not_in_quote(*start,
			input, start - input, ms) == 0)
		start++;
	command = ft_substr(input, 0, (start - input));
	mod->command = get_cmd_arr(command, ms);
	free(command);
	if (is_builtin(mod->command[0]))
		mod->builtin = 1;
	a = 0;
	while (mod->command[a])
		a++;
	check_dollar(mod->command, mod, ms);
	while (mod->command[a])
		a++;
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
