/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@hive.student.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:37:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/06/13 13:39:27 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void exit_code();

// shrink();

// char *add_value_back(char *value, );



// char *get_value(int start, int len , char *cmd, t_process_node *mod, t_shell *ms)
// {
// 	char *key;//USER
// 	int i;
// 	char *value;
	
// 	key = ft_calloc(len +  1);
// 	if (!key)
// 		return (NULL);
// 	while (i < len)
// 		key[i++]= cmd[start++];// copy key words from cmd to key
	
// 	i = 0;
// 	while(ms->envp[i])
// 	{
// 		if (ft_strncmp(key, envp[i], len) == 0)
// 		{
// 			value = (ft_strchr(envp[i], "=" ) + 1);// USER=yhsu    get the string after =
// 			add_value_back();//need to be protected
// 			break;;
// 		}
// 		else
// 		{
// 			shrink();
// 		}
					
// 		i++;
// 	}
		
// }


// char *expand_the_shit_out(char *cmd, t_process_node *mod, t_shell *ms)
// {  //"hello '$USER'"
// 	char *env;
// 	int i;
// 	int start;
// 	int quote;
// 	char *result;
	
// 	i = 0;
// 	//expand the variable
	

// 	quote = 0;
// 	while (cmd[i])//"hello '$PATH'"
// 	{
// 		if (*cmd == DOUBLEQUOTE && mod->process_mode == 0)
// 			mod->process_mode  = DOUBLEQUOTE;
// 		else if (*cmd == SINGLEQUOTE && mod->process_mode == 0)
// 			mod->process_mode  = SINGLEQUOTE;
// 		else if (*cmd == DOUBLEQUOTE && mod->process_mode == DOUBLEQUOTE)
// 			mod->process_mode  = 0;
// 		else if (*cmd == SINGLEQUOTE && mod->process_mode == SINGLEQUOTE)
// 			mod->process_mode  = 0;
	
		
// 		if (cmd[i] == '$' && mod->process_mode != SINGLEQUOTE))
// 		{
// 			if (cmd[i + 1] == '?' )
// 			{
// 				ms->exit_code = 10;
// 				expand_value(ft_itoa(10), );
// 				i++;
// 				continue;
// 			}
// 			while(cmd[i] == '$' )
// 				i++;
// 			start = i;//PATH
// 			while(ft_isalpha(cmd[i]) || cmd[i] == '_')
// 				i++;
// 			get_value(start, i - start, cmd[i]  process_node *mod, t_shell *ms); // need error handling		
			
// 			continuew;
// 		}
// 		else
// 			i++;
// 	}

	
// 	//delete quote
	
// }
// echo "3""'hello $USER'""7"
//echo $HOME
//echo $'HOME' = HOME
//echo '$HOME' = $HOME
//echo $"'HOME'" = 'HOME'

