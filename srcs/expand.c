/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:37:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/06/28 20:42:17 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void exit_code();

// char	*no_quote(char *cmd)//for test
// {
// 	char	*result;
// 	int		new_len;
// 	int		i;

// 	new_len = ft_strlen(cmd) - 1;
// 	result = malloc(sizeof(char) * new_len);
// 	if (result == NULL)
// 		ft_putstr_fd("malloc error", 2);// need change to print_error
// 	i = 0;
// 	while (i < new_len - 1)
// 	{
// 		result[i] = cmd[i + 1];
// 		i++;
// 	}
// 	result[i] = '\0';
// 	free(cmd);
// 	return (result);
// }

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

//char *add_value_back(char *value, int start, int len , char *cmd, char *envp )//
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
int	find_key_in_envp(t_shell *ms, char *key)
{
	int	i;

	i = 0;
	while (i < ms->envp_size) //iterates through the whole list
	{
		if (!key_exists(ms, key)) //doesn't match, then it will iterate through the list
			i++;
		else if (key_exists(ms, key)) //breaks if it equals or is at the end of list
			return (1);
	}
	return (0);
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

//void delete_quote(char *content, t_shell *ms)
char *delete_quote(char *content)
{
	char *temp;
	int len;
	
	
	dprintf(2, "1 delete quote content: %s\n", content);
	len = ft_strlen(content) - 1;
	dprintf(2, "len: %d\n", len);
	temp = ft_calloc(len, 1);
	//if (!temp)
		//error_handle
	temp = ft_strdup(content + 1);
	dprintf(2, "temp : %s\n", temp);
	ft_bzero(content, len);
	
	
	ft_strlcpy(content, temp, len); //temp + 1 to delete quote
	dprintf(2, "2 delete quote content: %s\n", content);
	free(temp);
	return (content);
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
		else if (mod->process_mode == SINGLEQUOTE)
			mod->process_mode = 0;
		else if ((mod->process_mode == DOUBLEQUOTE))
			mod->process_mode = 0;
	}
}



char *if_expandable(char *cmd, int i, t_process_node *mod, t_shell *ms)
{
	char *result;
	int start;
	//int j;

	start = i;//PATH
	if (ft_isalpha(cmd[i]) || cmd[i] == '_')
	{
		while(ft_isalpha(cmd[i]) || cmd[i] == '_')//check this
			i++;
		dprintf(2, "cmd in expandable: %s\n", cmd);
		//result = cmd;
		//dprintf(2, "0 result in expandable: %s\n", result);
		// if (mod->doublequote == -1 && mod->sinquote == -1)//no quote
		// {
			
		// 	result = get_value(start, i - start, cmd , ms); // need error handling
		// 	dprintf(2, "1 result in expandable: %s\n", result);
			
		// }
		// if (mod->doublequote != -1 && mod->sinquote != -1)//" '    ' "
		// {
		// 	if (mod->doublequote < mod->sinquote)
		// 		result = get_value(start, i - start, cmd , ms); // need error handling
		// }
		// if (mod->doublequote != -1 && mod->sinquote == -1)//no quote
		// {
		// 	result = get_value(start, i - start, cmd , ms); // need error handling
		// }
		result = get_value(start, i - start, cmd , ms);
		
	}
	else if(cmd[i] == '"' || (cmd[i] == '\'' && mod->process_mode != DOUBLEQUOTE))
	{
		result = cmd + i; //echo $'USER'   reusult = 'USER' 
	}	
	else if (cmd[i] == '?' ) //2nd letter ?->exit code
	{
		ms->exit_code = 10;//need more functions for exit code	
		//expand_exit_code(cmd, ms, );
	}
	// else if (cmd[i] == '$')
	// {
	// 	dprintf(2,"multi $\n");
	// 	j =  0;
	// 	while (cmd[j + i + 1] && cmd[i + j + 1] == '$')
	// 		j++;
		
	// 	result = cmd + i + j; 
	// 	dprintf(2,"%d times of j\n", j);
	// 	dprintf(2,"result:%s\n", result);
		
	// }
	
	
	return (result);
}

char *expand_it_out(char *cmd, t_process_node *mod, t_shell *ms)//send the whole line
{  //"hello '$USER'" change it to the correct value
	int j ;
	int i;
	char *result;
	
	i = 0;
	//result = cmd;//$USER
	mod->process_mode = 0;
	
	while (cmd[i])//"hello '$PATH'"
	{
		//dprintf(2, "in expand_it_out :%c\n", cmd[i]);
		check_quote(mod, cmd[i], i);
		//dprintf(2, "process_mode:%d\n",mod->process_mode);
		
		if (cmd[i] == '$'  && cmd[i+1] != '$' && ((mod->doublequote != -1 && mod->sinquote < mod->doublequote) || (mod->doublequote == -1 && mod->sinquote == -1))) //'" "'  ,  no quote
		{
			dprintf(2, "in expand_it_out cmd[i]:%c\n", cmd[i]);
			result = if_expandable(cmd, i + 1, mod, ms);	//$
			dprintf(2, "in expand_it_out reuslt:%s\n", result);
			break; 	
		}
		else if (cmd[i + 1] == '$')
		{
			dprintf(2,"multi $\n");
			j =  0;
			// while (cmd[j + i + 1] && cmd[i + j + 1] == '$')
			// 	j++;
			
			// result = cmd + i + j; 
			// dprintf(2,"%d times of j\n", j);
			// dprintf(2,"result:%s\n", result);
			while (cmd[i+j] == '$')
				j++;
			cmd[i] = cmd[i + j];
			continue;
		}
		else
			result = cmd;
		i++;
	}
	
	// //delete quote function
	// if ( mod->doublequote > -1 ||  mod->sinquote > -1)
	// {
	// 	dprintf(2, "in delete quote :%s\n", result);
		
	// 	//delete_quote(result, ms);
		
	// 	result = delete_quote(result);
	// 	dprintf(2, "result in delete quote: %s\n", result);
		
	// }
	// dprintf(2, "2 result in delete quote: %s\n", result);
	return (result);
}

//dont remoce quotes in expand, remove quotes in redierect

/*Test Cases*/
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
