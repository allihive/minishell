/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:29:00 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/30 10:59:38 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		// global_signal = 2;
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		write (1, "\n", 1);
		close(STDIN_FILENO);
		global_signal = 1;
	}
}

void heredoc_init(void)
{
    struct sigaction sa;
    struct sigaction sq;

    ft_bzero(&sa, sizeof(sa));
    ft_bzero(&sq, sizeof(sq));

    sa.sa_handler = heredoc_handler; //SIG_DFL//use SIG_DFL doesn't interfere and quits when it's supposed to
    sigaction(SIGINT, &sa, NULL);
    sq.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sq, NULL);
}

void get_heredoc_input(int heredoc_fd, t_process_node *process)//alice
{
    char *line;
    char *delimiter = NULL;

	heredoc_init();
    delimiter = (ft_strjoin( process->here_doc, "\n"));
	if (!delimiter)
		return ;
    // dprintf(2, "delimiter:%s\n", delimiter);
    // while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter) -2) != 0 )// need to fix this my delimiter has invisible char (ascii 22)
    while (global_signal != 2)
    {
		line = readline(">");
		printf("global signal %d\n", global_signal);
		if (!line)
		{
			error_msg("warning: ", "here-document at line 8 delimited by end-of-file (wanted ", delimiter);//error msg
			return ;
		}
        // dprintf(2, "get_heredoc_input line:%s\n", line);
        // dprintf(2, "get_heredoc_input delimiter:%s\n", delimiter);
		if (ft_strncmp(line, delimiter, (ft_strlen(delimiter) - 1)) == 0)
		{
			// printf("exits here1\n");
			free(line);
			return ;
		}
        if (ft_putstr_fd(line, heredoc_fd) == -1)
        {
			if (line)
            	free(line);
            line = NULL;
            free(delimiter);
            delimiter = NULL;
        }
		if (line)
        	free(line);
		line = readline(STDIN_FILENO);
        // printf("line=%s(%zu), delimiter=%s(%zu)\n", line, ft_strlen(line), delimiter, ft_strlen(delimiter));
        // printf("%d\n", ft_strncmp(line, delimiter, 3));
    }
	// set_signal();
    // while (1)//fix should change to g_signal != 1
    // {
    //     line = readline("> ");
    //     if (!line ||ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 )
    //         break;
    //     if (ft_putstr_fd(line, heredoc_fd) == -1)
    //     {
    //         free(line);
    //         line = NULL;
    //         free(delimiter);
    //         delimiter = NULL;
    //     }
    //     free(line);
    // }
    //dprintf(2, "process->here_doc:%s\n", process->here_doc);
}
*/
void get_heredoc_input(int heredoc_fd, t_process_node *process)//hsu
{
    char *line;
    char *delimiter = NULL;
    line = readline("> ");
    line = ft_strjoin(line, "\n");
    delimiter = (ft_strjoin( process->here_doc, "\n"));
    if (!delimiter)
        return ;
    //dprintf(2, "get_heredoc_input line:%s\n", line);
    //dprintf(2, "get_heredoc_input delimiter:%s\n", delimiter);
    while (1)
    {
        if (!line)
        {
            //error_msg("warning: ", "here-document at line 8 delimited by end-of-file (wanted ", delimiter);
            perror("here-document at line 8 delimited by end-of-file ");
            return ;
        }
        if (ft_strncmp(line, delimiter, (ft_strlen(delimiter) - 1)) == 0)
        {
            free(line);
            return ;
        }
        if (ft_putstr_fd(line, heredoc_fd) == -1)
        {
            if (line)
                free(line);
            line = NULL;
            free(delimiter);
            delimiter = NULL;
        }
        if (line)
            free(line);
        line = readline("> ");
        line = ft_strjoin(line, "\n");
    }
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
	
	// signal_heredoc(1);
    get_heredoc_input(heredoc_fd, process);
	printf("finished get_heredoc_input\n");
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