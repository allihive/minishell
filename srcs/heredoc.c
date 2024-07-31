/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:29:00 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/31 13:56:08 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_heredoc(char *line, char *delimiter, int	stdin_backup, int heredoc_fd)
{
	if (line == NULL)
	{
		if (global_signal == 2)
		{
			dup2(stdin_backup, STDIN_FILENO);
			global_signal = 0;
			return (0);
		}
		heredoc_input_msg(delimiter);
		return (0);
	}
	if (ft_strncmp(line, delimiter, (ft_strlen(delimiter) + 1) ) == 0)
	{
		free(line);
		return (0);
	}
	if (ft_putstr_fd(line, heredoc_fd) == -1)
	{
		if (line)
			free(line);
		line = NULL;
		free(delimiter);
		delimiter = NULL;
	}
	return (1);
}

void get_heredoc_input(int heredoc_fd, t_process_node *process)
{
    char *line = NULL;
    char *delimiter = NULL;
	int stdin_backup;

	stdin_backup =	dup(STDIN_FILENO);
	heredoc_init();
	delimiter = process->here_doc;
	if (!delimiter)
		return ;
	line = readline("> ");
	while (1)
    {
		if (output_heredoc(line, delimiter, stdin_backup, heredoc_fd) == 0)
			return ;
		if (line)
        	free(line);
		line = readline("> ");
		write (heredoc_fd, "\n", 1);
    }
	dup2(stdin_backup, STDIN_FILENO);
	global_signal = 0;
	return;
}


int right_delimiter(char *redirect,  t_process_node *process)// too many lines can remove tmp just use redirect 
{
    char *end;
    char *tmp = redirect;

    while (ifisspace(*redirect))
        redirect++;
    end = redirect;
    tmp = redirect;
    while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
    if (process->here_doc == NULL) 
    {
        //process->here_doc = malloc(sizeof(char *) * 100); // Define MAX_REDIRECTS appropriately
        process->here_doc = calloc(100, sizeof(char *));
        if (process->here_doc== NULL) 
        {
            perror("heredoc in malloc");
            return (1); // Handle error or return as appropriate
        }
        //ft_memset(process->here_doc, 0, sizeof(char *) * 100); // Initialize to NULL
    }
    tmp = ft_substr(redirect, 0, end - tmp);
    if (!tmp) 
    {
        perror("heredoc in malloc");
        return (1); // Handle error or return as appropriate
    }
    if (*tmp == '"' || *tmp == '\'')
        tmp = remove_quote(tmp, ft_strlen(tmp) - 1);
    process->here_doc = tmp;
    return (0);
}

int handle_heredocs(char *redirect, t_process_node *process,t_shell *ms)
//int handle_heredocs(char *redirect, t_process_node *process)
{// << end
    int heredoc_fd;
    static int i;
    char *heredoc_name;

    i = 0;
    process->heredoc = i;
    i++;
    heredoc_name = ft_strjoin(".heredoc", ft_itoa(i));
    redirect+= 2;
	
    //process->here_doc = right_delimiter(redirect, process);//delimiter: end
	
    if (right_delimiter(redirect, process))
    {
        perror("open .heredoc failed");
        return(set_exitcode(ms, 1)); 
    }   
    close(ms->fd[0]);
    heredoc_fd = open(heredoc_name, O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0777);
    
    if (heredoc_fd == -1)
    {
        perror("open .heredoc failed");
        return(set_exitcode(ms, 1)); 
    }
    get_heredoc_input(heredoc_fd, process);
    if (close(heredoc_fd) == -1)
    {
        perror("open .heredoc failed");
        return(set_exitcode(ms, 1)); 
    }
    ms->fd[0] = open(heredoc_name, O_RDONLY);
    if (ms->fd[1] == -1)
    {
        perror("open .heredoc failed");
        return(set_exitcode(ms, 1)); 
    }
    unlink(heredoc_name);
    free(heredoc_name);
    return (0);
}