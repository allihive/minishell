/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 15:24:23 by alli             ###   ########.fr       */
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

void check_redir_quote(char *tmp, int *quote_status)
{
	int l;
	int quote;

	quote = -1;
	l = 0;
	while (tmp[l])
	{
		if (tmp[l] == DOUBLEQUOTE && quote == -1)
			quote = DOUBLEQUOTE;
		else if (tmp[l] == DOUBLEQUOTE && quote == DOUBLEQUOTE)
			quote = -1;
		else if (tmp[l] == SINGLEQUOTE && quote == -1)
			quote = SINGLEQUOTE;
		else if (tmp[l] == SINGLEQUOTE && quote == SINGLEQUOTE)
			quote = -1;
		l++;
	}
	*quote_status = quote;
}

int	redirect_not_in_quote(char c, char *input, int k, t_shell *ms)
{
	int		quote_status;
	//int		l;
	char	*tmp;

	//quote = -1;
	//l = 0;
	if (c == '<' || c == '>')
	{
		tmp = ft_substr(input, 0, k);
		check_redir_quote(tmp, &quote_status);
		
		// while (tmp[l])
		// {
		// 	if (tmp[l] == DOUBLEQUOTE && quote == -1)
		// 		quote = DOUBLEQUOTE;
		// 	else if (tmp[l] == DOUBLEQUOTE && quote == DOUBLEQUOTE)
		// 		quote = -1;
		// 	else if (tmp[l] == SINGLEQUOTE && quote == -1)
		// 		quote = SINGLEQUOTE;
		// 	else if (tmp[l] == SINGLEQUOTE && quote == SINGLEQUOTE)
		// 		quote = -1;
		// 	l++;
		// }
		free (tmp);
		if (quote_status != -1)
			return (0);
		else
		{
			ms->execute = -1;
			return (1);
		}
	}
	else
		return (0);
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
