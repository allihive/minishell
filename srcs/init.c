/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:46:29 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/02 14:48:32 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





int unclosed_quote(char *line)
{
	char delim;

	while(line)
	{
		delim = check_delimiter(line);//確認有沒有delimiter
		
		if (!delim)
			return (0);
		line = ft_strchr(line, delim);//把line指導有分隔號的地方
		if (!ft_strchr(line + 1, delim))
			return(delim);//果沒有成雙就返回表示錯誤
		line = ft_strchr(line + 1, delim) + 1;//將指針移到第二個分隔符號後，繼續檢查
	}
	return (0);
}


int check_syntax(char *line, t_shell *ms)// mutiple pipe ... back slash, : export > ( syntax error near unexpected token `newline')
{
	char quote;

	if (!line || !*line || *line == '|' || *(line + ft_strlen(line) - 1) == '|')//檢查空輸入和管道符號
		return (syntax_error("`|'", ms));//要改 error handling
	quote = unclosed_quote(line);//檢查未關閉的引號
	if (quote == SINGLEQUOTE)
		return (syntax_error("`\''", ms));
	else if (quote == DOUBLEQUOTE)
		return (syntax_error("`\"'", ms));
	if (invalid_redirect(line, '>'))//檢查無效的重定向
		return (syntax_error("`>'", ms));
	else if (invalid_redirect(line, '<'))
		return (syntax_error("`<'", ms));
	return (0);
}


void init_node(t_process_node *new, char *line, char *temp)
{
	new->append = -1;
	new->heredoc = -1;
	new->expand = -1;
	new->doublequote = -1;
	new->sinquote = -1;
	new->redirectin = -1;
	new->redirectout= -1;
	//new->redirs = NULL;
	new->command = NULL;
	new->node_line= NULL;// = input
	new->redirect_in= NULL;//< input
	new->redirect_out= NULL;//> output
	new->append_s= NULL;//>>append
	new->here_doc= NULL;//<<
	new->cmd_path = NULL;
	new->node_line = ft_substr(line, 0, (temp - line));
	if (!new->node_line )
		free(new->node_line);
}

int init_shell(t_shell *ms)
{
	ms->count = 0;
	ms->read_end = -1;
	ms->fd[0] = dup(0);//init as stdin
    ms->fd[1] = dup(1);
	ms->execute = 0;
	ms->fork_n = count_cmd(ms->list);
	ms->pids = ft_calloc((ms->fork_n + 1), sizeof(int));//data->cmds, sizeof(int)
	if (!ms->pids)
		return (close_and_free(ms));
	ms->pids[0] = -1;
	return (0);
}

int init_process_node(char *line, t_shell *ms)
{
    t_process_node *new;
	char *temp;
    
	if (!line || !*line || check_syntax(ms->line, ms) || empty_prompt(line))
        return (set_exitcode(ms, -1));
	while (*line)
    {
		while (ifisspace(*line))
            line++;
			
        temp = point_end(line); 
        new = ft_calloc(1, sizeof(t_process_node));
		if (!new)
        	error_handle(ms);
		init_node(new, line, temp);
		append_process_node(&ms->list, new);// save every command in a node and append them to a list	
		check_syntax(new->node_line, ms);
		line = temp;
		if(*line)
			line++; //跳過pipe
    }
	init_shell(ms);
	return (0);
}


