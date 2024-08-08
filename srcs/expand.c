/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:37:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/08 16:05:10 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_value(int start, int len , char *cmd, t_shell *ms)
{
	char *key;//USER
	int i;
	char *value;
	int value_start;

	value_start = start;//after quotes and dollar signs
	key = ft_calloc(len + 1, sizeof(int));
	if (!key)
		return (NULL);
	i = 0;
	while (i < len)
		key[i++]= cmd[start++];// copy key words from cmd to key
	if (!find_key_in_envp(ms, key)) // when it's at the end of the list we should go into the shrink function
	{
		cmd = shrink(cmd, value_start - 1); //error handle check?
	}
	if (key_exists(ms, key))
	{
		value = find_value(ms, key);
		cmd = add_value_back(value, value_start, len, cmd);
	}
	free(key);
	return (cmd);
}

char *remove_dollar_sign(char *cmd, int dollar, int amount)//(cmd, key - 1, 1);
{
	int	i;
	char *temp;

	i = 0;
	temp = cmd;
	
	if (temp[dollar + i] != '$')
		i++;
	while (temp[dollar + amount + i])
	{
		cmd[dollar + i] = temp[dollar + amount + i];
		i++;
	}
	cmd[dollar + i] = '\0';
	return (cmd);
}
char	*echo_exit_code(t_shell *ms)
{
	char *exit_code;

	exit_code = ft_itoa(ms->excode);
	if (!exit_code)
		return (NULL);
	// ft_putstr_fd(exit_code, 1);
	return (exit_code);
}

char *echo_digit(char *cmd, t_shell *ms, int i)
{	
	char *replace;
	int	len;
	int j;

	j = 0;
	// printf("cmd: %s\n", cmd);
	len = ft_strlen(cmd) - 2;
	// printf("len: %d\n", len);
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

char *if_expandable(char *cmd, t_shell *ms, int i, t_process_node *mod ) // i = key
{
	char *result = NULL;
	int start;
	
	start = i;//PATH
	if (ft_isalpha(cmd[i]) || cmd[i] == '_' ) //why does this have to be alpha?
	{
		while(cmd[i] == '_' || ft_isalnum(cmd[i]))//check this with yunchia ft_isalpha(cmd[i])
			i++;
		result = get_value(start, i - start, cmd, ms);
	}
	else if(cmd[i] == '"' || (cmd[i] == '\'' && mod->process_mode != DOUBLEQUOTE))
	{
		result = ft_strdup(cmd + i); //echo $'USER'   reusult = 'USER' 
		free (cmd);
	}
	else if (cmd[i] == '?' ) //2nd letter ?->exit code
	{
		// dprintf(2, "3 in expandable\n");
		result = echo_exit_code(ms);
		free(cmd);
	}
	else if (ft_isdigit(cmd[i]))
		result = echo_digit(cmd, ms, i);
	else if(cmd[i] == '"' || (cmd[i] == '\'' && mod->process_mode == DOUBLEQUOTE))
		result = cmd; //echo "$'HOME'"
	return (result);
}


char *expand_it_out(char *cmd, t_process_node *mod, t_shell *ms)//send the whole line
{  //"hello '$USER'" change it to the correct value
	int i;
	char *result;
	
	i = 0;
	mod->process_mode = 0;
	while (cmd[i])//"hello '$PATH'"
	{
		check_quote(mod, cmd[i], i);

		if (cmd[i] == '$'  && ((mod->doublequote != -1 && mod->sinquote < mod->doublequote) || (mod->doublequote == -1 && mod->sinquote == -1))) //'" "'  ,  no quote
		{
			if ( cmd[i + 1] == '$')
			{
				result = remove_dollar_sign(cmd, i, 1);
				continue;
			}
			result = if_expandable(cmd, ms, i + 1, mod);	//$
			break;
		}
		else
			result = cmd;
		i++;
	}
	return (result);
}


/*Test Cases*/
//echo hello $USEroijg haha prints hello haha
// echo "3""'hello $USER'""7"
// echo $HOME
// echo "hello '$HOME'"
//export VAR=echo; $VAR helloo -> helloo
// X echo $'HOME' = HOME 
// X echo '$HOME' = $HOME
// X echo $"'HOME'" = 'HOME'
//1 $? exit code
//2 $valid able to expand can find in envp
//3rd $not valid, then shrink remove $ and string after it, if ithere is a space, and you have to print the string after the space
