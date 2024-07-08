/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:37:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/06/27 08:29:49 by alli             ###   ########.fr       */
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
	// char *temp; //had to comment out because of linux
	int i = 0;
	int j = 0;
	int		rest_of_str;
	
	new = ft_calloc((ft_strlen(cmd) - len + 1 + ft_strlen(value)) , sizeof(char));// cmd 長度  減 value + 1  + 新從envorinmental variables 找到得直
	//加前段
	while (i < start - 1)//copies echo "hello $USER" copies double quote hello_
	{
		new[i] = cmd[i];
		i++;
	}		
	j = 0;
	//加擴張的
	while(value[j])
		new[i++] = value[j++]; //hello yshu replace the $USER->yhsu
	//dprintf(2, "2new in add value: %s\n", new);	
	if(j < len)
		len = j;//? count the value
	//加後段
	rest_of_str = start + len; //$USER after that
	while(cmd[rest_of_str])
		new[i++] = cmd[rest_of_str++];
	//dprintf(2, "3new in add value: %s\n", new);	
	// temp = cmd; //commented out for linux
	cmd = new;
	//free(temp); // don't free causes double free
	dprintf(2, "cmd in add_value_back: %s\n", cmd);
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


char *expand_the_shit_out(char *cmd, t_process_node *mod, t_shell *ms)//send the whole line
{  //"hello '$USER'" change it to the correct value
	
	int i;
	int start;
	// int quote; //commented out for linux
	char *result;
	
	i = 0;
	//expand the variable
	
	result = cmd;//$USER
	// quote = 0; //commented out for linux
	while (cmd[i])//"hello '$PATH'"
	{
		dprintf(2,"icmd[i]%c\n",cmd[i]);
		if (*cmd == DOUBLEQUOTE && mod->process_mode == 0) //1st double quote
			mod->process_mode  = DOUBLEQUOTE;
		else if (*cmd == SINGLEQUOTE && mod->process_mode == 0)//1st single quote
			mod->process_mode  = SINGLEQUOTE;
		else if (*cmd == DOUBLEQUOTE && mod->process_mode == DOUBLEQUOTE)//175-178 commented
			mod->process_mode  = 0; //closing quote
		else if (*cmd == SINGLEQUOTE && mod->process_mode == SINGLEQUOTE)
			mod->process_mode  = 0; //170-178 checking single quote or double quote mark it
		dprintf(2,"mod->process_mode %d\n", mod->process_mode);
		if (cmd[i] == '$' && mod->process_mode != SINGLEQUOTE) //process_mode integer
		{
			
			dprintf(2,"in get shit out\n");
			if (cmd[i + 1] == '?' ) //2nd letter ?->exit code
			{
				ms->exit_code = 10;//need more functions for exit code
				
				//add_value_back(0 , 2 , ft_itoa(10), NULL ); // 要把code加進去
				i++;
				continue;
			}
			while(cmd[i] == '$')//multiple dollar signs, then print other ones
				i++;
			start = i;//PATH
			while(ft_isalpha(cmd[i]) || cmd[i] == '_')//check this
				i++;
			result = get_value(start, i - start, result , ms); // need error handling		
			dprintf(2,"in expand_the_shit_out result:%s\n", result);
			// continue; will continue the loop
			break ; //break will leave the loop
		}
		else
			i++;
	}
	dprintf(2,"at the end result:%s\n", result);
	//delete quote function
	return (result);
}

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
