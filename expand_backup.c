/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_backup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:37:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/07 12:21:01 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_flag(t_flags *f)
{
	f->in_single = -1;
	f->in_double = -1;
}

char *remove_quote(char *str, int len)
{
	char *new_str;
	int i;
	int j;
	t_flags f;

	i = 0;
	j = 0;
	init_flag(&f);
	new_str = ft_calloc(len, sizeof(char));
	if (!new_str)
		return (NULL);
	while(str[i])
	{
		if (str[i] == '\'' && f.in_double == -1)
			f.in_single *= -1;	
		else if (str[i] == '"' && f.in_single == -1)
			f.in_double *= -1;
		else
			new_str[j++] = str[i];	
		i++;
	}
	free(str);
	return (new_str);	
}

int count_quote(char *str)
{
	int i;
	int quote_n;
	t_flags f;

	init_flag(&f);
	i = 0;
	quote_n = 0;
	while(str[i])
	{
		if (str[i] == '\'' && f.in_double == -1)
		{
			quote_n++;
			f.in_single *= -1;
		}	
		if (str[i] == '"' && f.in_single == -1)
		{
			quote_n++;
			f.in_double *= -1;
		}	
		i++;	
	}
	return (quote_n);
}


char *quote_remover(char *str)
{
	int remove_q;
	int len;

	remove_q = count_quote(str);
	len = ft_strlen(str) - remove_q + 1;
	return (remove_quote(str, len));
}



static int	key_exists(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	len = 0;
	while(name[i] && name[i] != '=')
		i++;
	key = ft_substr(name, 0, i + 1);
	if (!key)
		return (0); //should be error_handle
	len = ft_strlen(key);
	i = 0;

	while (i < ms->envp_size && ms->envp[i])
	{
		if ((ft_strncmp(key, ms->envp[i], len) == 0) 
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
				return (1);// key is found
		i++;
	}
	free(key);
	return (0);
}


char *shrink(char *cmd, int remove) //if something after $ is invalid still print something before and after
{
	int i = 0;
	int j = 0;
	char *temp;
	char *new;
	
	new = ft_calloc(ft_strlen(cmd), sizeof(char)); //cannot be expanded, the delete the dollar sign
	if (!new)
		return (NULL);
	while(cmd[i] && i != remove) //shrink copy first part skip dollar sign and invalid env, copy rest of itif there is any and send it back
		new[j++] = cmd[i++];
	while (cmd[i] && cmd[i]!= ' ')
		i++;
	i++;
	new[j+1] = ' ';
	while(cmd[i - 1])
		new[j++] = cmd[i++];
	temp = cmd;
	cmd = new;
	free (temp);
	return (cmd);
	//echo hello $USEroijg haha prints hello haha
}

char *add_value_back( char *value, int start, int len , char *cmd)//expand
{
	char *new;
	//char *temp; //had to comment out because of linux
	int i = 0;
	int j = 0;
	int		rest_of_str;
	
	new = ft_calloc((ft_strlen(cmd) - len + 1 + ft_strlen(value)) , sizeof(char));// cmd 長度  減 value + 1  + 新從envorinmental variables 找到得直
	//char before $
	while (i < start - 1)//copies echo "hello $USER" copies double quote hello_
	{
		new[i] = cmd[i];
		i++;
	}		
	j = 0;
	//env value
	while(value[j])
		new[i++] = value[j++]; //hello yshu replace the $USER->yhsu
	//dprintf(2, "2new in add value: %s\n", new);	
	if(j < len)
		len = j;//? count the value
	//add the rest char
	rest_of_str = start + len; //$USER after that
	while(cmd[rest_of_str])
		new[i++] = cmd[rest_of_str++];
	
	
	//temp = cmd;
	cmd = new;
	//free(temp); // don't free causes double free
	//dprintf(2, "cmd in add_value_back: %s\n", cmd);
	return (new);
}

char	*find_value(t_shell *ms, char *key)
{
	int	i;
	int	len;
	char *value;

	i = 0;
	len = ft_strlen(key);
	while (ms->envp[i])
	{
		if(!ft_strncmp(key, ms->envp[i], ft_strlen(key)) && (ms->envp[i][len] == '\0'  || ms->envp[i][len] == '='))
		{
			value = (ft_strchr(ms->envp[i], '=') + 1); // USER=yhsu    value = yhsu
			return(value);
		}
		i++;
	}
	return (NULL);
}
char	*find_key_in_envp(t_shell *ms, char *key)
{
	int	i;

	i = 0;
	while (i < ms->envp_size) //iterates through the whole list
	{
		if (!key_exists(ms, key)) //doesn't match, then it will iterate through the list
			i++;
		else if (key_exists(ms, key)) //breaks if it equals or is at the end of list
			return (key);
	}
	return (NULL);
}

char *get_value(int start, int len , char *cmd, t_shell *ms)
{
	char *key;//USER
	int i;
	char *value;
	int value_start;

	value_start = start;//after quotes and dollar signs
	key = ft_calloc(len + 1, sizeof(char));
	if (!key)
		return (NULL);
	i = 0;
	while (i < len)
		key[i++]= cmd[start++];// copy key words from cmd to key
	if (!find_key_in_envp(ms, key)) // when it's at the end of the list we should go into the shrink function
		cmd = shrink(cmd, value_start - 1); //error handle check?
	if (key_exists(ms, key))
	{
		value =  find_value(ms, key);
		cmd = add_value_back(value, value_start, len, cmd);//need to be protected //changed start to value start
		//keep the single quote inside, double quote inside, don't need to expand, then keep double quote inside
	}
	free(key);
	return (cmd);
}


void	check_quote(t_process_node *mod, char c, int i)
{
	if (c == '\'' || c == '"')
	{
		if (mod->process_mode == 0 )
		{
			if (c == '\'')
			{
				mod->process_mode = SINGLEQUOTE;
				mod->sinquote = i;
			}
			else
			{
				mod->process_mode = DOUBLEQUOTE;
				mod->doublequote = i;
			}
		}
		else if (c == '\''  && mod->process_mode == SINGLEQUOTE)
			mod->process_mode = 0;
		else if (c == '"' && mod->process_mode == DOUBLEQUOTE)
			mod->process_mode = 0;
	}
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
		
		//dprintf(2, "i:%d\n", i);
		//dprintf(2, "temp[dollar + amount + i]:%c\n", temp[dollar + amount + i]);
		cmd[dollar + i] = temp[dollar + amount + i];
		//dprintf(2, "cmd[dollar + i]:%c\n", cmd[dollar + i]);

		i++;
	}
	cmd[dollar + i] = '\0';
	//dprintf(2, "cmd in remove dollar:%s\n", cmd);
	return (cmd);
}
char	*echo_exit_code(t_shell *ms)
{
	char *exit_code;

	printf("in echo_exit %d\n", ms->excode);
	exit_code = ft_itoa(ms->excode);
	if (!exit_code)
		return (NULL);
	printf("in echo_exit str %s\n", exit_code);
	ft_putstr_fd(exit_code, 1);
	return (exit_code);
}
char *if_expandable(char *cmd, t_shell *ms, int i, t_process_node *mod ) // i = key
{
	char *result = NULL;
	int start;
	//int j;
	start = i;//PATH

	if (ft_isalpha(cmd[i]) || cmd[i] == '_' ) //why does this have to be alpha?
	{
		dprintf(2, "0 in expandable\n");
		while(cmd[i] == '_' || ft_isalnum(cmd[i]))//check this with yunchia ft_isalpha(cmd[i])
			i++;
		result = get_value(start, i - start, cmd, ms);
	}
	if (ft_isalpha(cmd[i]) || cmd[i] == '_' )
	{
		dprintf(2, "1 in expandable\n");
		while(ft_isalpha(cmd[i]) || cmd[i] == '_')//check this
			i++;
		result = get_value(start, i - start, cmd , ms);	
	}
	else if(cmd[i] == '"' || (cmd[i] == '\'' && mod->process_mode != DOUBLEQUOTE))
	{
		dprintf(2, "2 in expandable\n");
		result = cmd + i; //echo $'USER'   reusult = 'USER' 
	}
	else if (cmd[i] == '?' ) //2nd letter ?->exit code
	{
		dprintf(2, "3 in expandable\n");
		result = echo_exit_code(ms);
	}
	else if(cmd[i] == '"' || (cmd[i] == '\'' && mod->process_mode == DOUBLEQUOTE))
	{
		dprintf(2, "4 in expandable\n");
		result = cmd; //echo "$'HOME'"
	}
	return (result);
}

char *expand_it_out(char *cmd, t_process_node *mod, t_shell *ms)//send the whole line
{  //"hello '$USER'" change it to the correct value
	//int j ;
	int i;
	char *result;
	
	i = 0;
	//result = cmd;//$USER
	//dprintf(2, "cmd %s in expand it out\n", cmd);//"$'HOME'"
	mod->process_mode = 0;
	// printf("ms->excode in expand_it_out %d\n", ms->excode);
	while (cmd[i])//"hello '$PATH'"
	{
		//dprintf(2, "1 expand it out\n");
		check_quote(mod, cmd[i], i);

	
		if (cmd[i] == '$'  && ((mod->doublequote != -1 && mod->sinquote < mod->doublequote) || (mod->doublequote == -1 && mod->sinquote == -1))) //'" "'  ,  no quote
		{
			
			if ( cmd[i + 1] == '$')
			{
				cmd = remove_dollar_sign(cmd, i, 1);
				continue;
			}
			result = if_expandable(cmd, ms, i + 1, mod);	//$
			//result = quote_remover(result);
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
