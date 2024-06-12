/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/06/12 13:12:17 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /* return 1 if char c is a spaces */
// int ifisspace(char c)
// {
// 		if (c == 32 || (c <= 9 && c >= 13))
// 			return (1);	
// 	return (0);
// }

// int ifismeta (char c)
// {
// 	if (c == ';' || c == '$' || c == '\'' || c == '\'')
// 		return (c);
// 	else
// 		return (0);
// }
// char *point_end(char *line)
// {
//     while (*line)
//     {
//         while (*line && *line != '|' && *line != '\"' && *line != '\'')
//           line++;
//         if (*line == '\"' || *line == '\'')
//         {
//             line++;
//             while(*line && *line != '|' && *line != '\"' && *line != '\'')
//               line++;
            
//         }
//         else
//           return(line);
        
//     }
//     return(line);
// }

// char check_delimiter(line);
// {
// 	char *single_quote;
// 	char *doublele_quote;

// 	single_quote = ft_strchr(line, '\'');
// 	doublele_quote = ft_strchr(line, '\"')
// 	if (!single_quote && !double_quote)
// 		return (0);
// 	else if ((single_quote && double_quote) && (single_quote > double_quote))
// 		return ('\"');
// 	else if (single_quote && double_quote)
// 		return ('\'');
// 	else if (double_quote)
// 		return ('\"');
// 	else 
// 		return ('\'');
// }
	

// int unclosed_quote(char *line)
// {
// 	char delim;

// 	while(line)
// 	{
// 		delim = check_delimiter(line);//確認有沒有delimiter
		
// 		if (!delim)
// 			return (0);
// 		line = ft_strchr(line, delim);//把line指導有分隔號的地方
// 		if (!ft_strchr(line + 1, delim))
// 			return(delim);//果沒有成雙就返回表示錯誤
// 		line = ft_strchr(line + 1, delim) + 1;//將指針移到第二個分隔符號後，繼續檢查
// 	}
// 	return (0);
// }

// int invalid_redirect( char *line, char redirect)
// {
// 	while(*line)
// 	{
// 		if (*line == '$' || (*line != redirect && *line != ifismeta(*line)))
// 			line++;
// 		else if (ifismeta(*line))// ' '' : 
// 		{
// 			line++;
// 			while (*line && *line != '\'' && *line != '\"')//echo "Hello World"
// 				line++;
// 			line++;//skip ' or "
		
// 		}
// 		else
// 		{
// 			line++;
// 			if (*line == redirect)
// 				line++;
// 			if (ifisspace(*line))
// 				line++;
// 			if (!*line || *line == '<' ||*line == '>')
// 				return (1);//fail
// 		}
// 	}
// 	return (0);
// }



// int check_syntax(char *line, t_shell *ms);// mutiple pipe ... back slash, : export > ( syntax error near unexpected token `newline')
// {
// 	char quote;
// //檢查空輸入和管道符號
// 	if (!line ||! *line || *line == '|' || *(line + ft_strlen(line) - 1) == '|')
// 		return (syntax_error());
// //檢查未關閉的引號
// 	quote = unclosed_quote(line);
// 	if (quot == '\'')
// 		return (syntax_error());
// 	else if (quot == '\"')
// 		return (syntax_error());
// //檢查無效的重定向
// 	if (invalid_redirect(line, '>'))
// 		return (syntax_error());
// 	else if (invalid_redirect(line, '<'))
// 		return (syntax_error());
// 	return (0);
// }

// void append_process_node(t_process_node *list, t_process_node *new)
// {
// 	t_process_node *last_node;
// 	if (new == NULL)
// 		list = new;
// 	else
// 	{
// 		last_node= new;
// 		while(new->next)
// 			last_node = last_node->next;
// 		last_node->next = new;
// 	}
// 	new->next = NULL;
// }

// int count_cmd(t_process_node *list)
// {
// 	int n;
	
// 	n = 0;
// 	while (list)
// 	{
		
// 		list = list->next;
// 		n++;
// 	}
// 	return (n);	
// }

// int init_process_node(char *line, t_shell *ms)
// {
//     t_process_node *new;
//     char *temp;

//     if (!line || !*line || check_syntax(ms->line, ms) || ifisspace(line))
//         return (false);
//     while (line)
//     {

//         while (ifisspace(line))
//             line++;

//         //make temp point to the end of the
//         temp = point_end(line); 


//         //calloc for new 
//         new = ft_calloc(1, sizeof(t_process_node));
//         // if (!new)
//         //     error_handle();
//         new->fd_in = -1;
//         new->fd_out = -1;
// 		new->command = NULL;
//         if (new->node_line)
//             new->node_line = ft_substr(line, 0, (temp - line));
//         if (!new->node_line )
//             free(new->node_line );
// 		append_process_node(ms->list, new);// save every command in a node and append them to a list
// 		check_syntax(new->node_line, ms);
// 	// malloc pids
// 		line = temp;
// 		if(*line)
// 			line++; //跳過pipe
//     }
// 	ms->fork_n = count_cmd(ms->list);
// 	ms->pids = ft_calloc(1,ms->fork_n * sizeof(pid_t));
// 	return (0);
// }

// void parse_mod(char *input, t_process_node mod, t_shell ms)
// {
// 	while( *input)//  echo "hello $USER" > infile.txt
// 	{
// 			//檢查redirevt

// 			//
// 	}
// }


// void parse_process_node(t_process_node *list, t_shell *ms)
// {
// 	t_process_node *mod;//command node
// 	char *input;

// 	while (mod)
// 	{
// 		input = mod->node_line;
// 		parse_mod(input, mod, ms);

// 		//if (mod->command != NULL)
// 			//parse_expands(mod, ms);??

// 		mod = mod->next;
// 	}
// }

// static void execute_shell(t_shell *ms)
// {
// 	parse_process_node(&ms->list, ms); //oritginal:parse_modules(&ms->mods, ms)
// 	//execute_children(ms);
// 	//wait_children(ms);
// }
