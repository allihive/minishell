/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:37:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/08 18:03:18 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(int start, int len, char *cmd, t_shell *ms)
{
	char	*key;
	int		i;
	char	*value;
	int		value_start;

	value_start = start;
	key = ft_calloc(len + 1, sizeof(int));
	if (!key)
		return (NULL);
	i = 0;
	while (i < len)
		key[i++] = cmd[start++];
	if (!find_key_in_envp(ms, key))
	{
		cmd = shrink(cmd, value_start - 1);
	}
	if (key_exists(ms, key))
	{
		value = find_value(ms, key);
		cmd = add_value_back(value, value_start, len, cmd);
	}
	free(key);
	return (cmd);
}



char	*echo_digit(char *cmd, t_shell *ms, int i)
{	
	char	*replace;
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(cmd) - 2;
	replace = malloc((sizeof(char) * len) + 1);
	if (!replace)
		return (NULL);
	i++;
	while (cmd[i])
	{
		replace[j] = cmd[i];
		j++;
		i++;
	}
	free(cmd);
	ms->excode = 0;
	return (replace);
}

static char	*expand_str(int start, char *cmd, t_shell *ms, int i)
{		
	char *result;
	
	while (cmd[i] == '_' || ft_isalnum(cmd[i]))
		i++;
	result = get_value(start, i - start, cmd, ms);

	return (result);

}

char	*if_expandable(char *cmd, t_shell *ms, int i, t_process_node *mod )
{
	char	*result;
	int		start;

	result = NULL;
	start = i;
	if (ft_isalpha(cmd[i]) || cmd[i] == '_' )
	{
		result = expand_str(start, cmd, ms, i);
		
		// while (cmd[i] == '_' || ft_isalnum(cmd[i]))
		// 	i++;
		// result = get_value(start, i - start, cmd, ms);
	}
	else if (cmd[i] == '"' || (cmd[i] == '\''
			&& mod->process_mode != DOUBLEQUOTE))
	{
		result = ft_strdup(cmd + i);
		free (cmd);
	}
	else if (cmd[i] == '?' )
	{
		result = echo_exit_code(ms);
		free (cmd);
	}
	else if (ft_isdigit(cmd[i]))
		result = echo_digit(cmd, ms, i);
	else if (cmd[i] == '"' || (cmd[i] == '\''
			&& mod->process_mode == DOUBLEQUOTE))
		result = cmd;
	return (result);
}

char	*expand_it_out(char *cmd, t_process_node *mod, t_shell *ms)
{
	int		i;
	char	*result;

	i = 0;
	mod->process_mode = 0;
	while (cmd[i])
	{
		check_quote(mod, cmd[i], i);
		if (cmd[i] == '$' && ((mod->doublequote != -1
					&& mod->sinquote < mod->doublequote)
				|| (mod->doublequote == -1 && mod->sinquote == -1)))
		{
			if (cmd[i + 1] == '$')
			{
				result = remove_dollar_sign(cmd, i, 1);
				continue ;
			}
			result = if_expandable(cmd, ms, i + 1, mod);
			break ;
		}
		else
			result = cmd;
		i++;
	}
	return (result);
}
