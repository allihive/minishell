

#include "minishell.h"

void get_heredoc_input(int heredoc_fd, t_process_node *process)
{
    char *line;
    char *delimiter = NULL;

    line = get_next_line(STDIN_FILENO);
    delimiter = (ft_strjoin( process->here_doc, "\n"));
    dprintf(2, "get_heredoc_input line:%s\n", line);
    dprintf(2, "get_heredoc_input delimiter:%s\n", delimiter);
    while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0 )
    {
        dprintf(2," here0\n");
        if (ft_putstr_fd(line, heredoc_fd) == -1)
        {
            free(line);
            line = NULL;
            free(delimiter);
            delimiter = NULL;
        }
        free(line);
        line = get_next_line(STDIN_FILENO);
    }
    dprintf(2, "process->here_doc:%s\n", process->here_doc);
}

char *right_delimiter(char *redirect,  t_process_node *process)
{
    char *end;
    char *tmp = redirect;

    while (ifisspace(*redirect))
        redirect++;
    end = redirect;
    tmp = redirect;
    while (*end && !ifisredirect(*end))
		end++;

    if (process->here_doc == NULL) 
    {
        process->here_doc = malloc(sizeof(char *) * 100); // Define MAX_REDIRECTS appropriately
        if (process->here_doc== NULL) 
        {
            perror("heredoc in malloc");
            return NULL; // Handle error or return as appropriate
        }
        ft_memset(process->here_doc, 0, sizeof(char *) * 100); // Initialize to NULL
    }
    tmp = ft_substr(redirect, 0, end - tmp);
    dprintf(2, "tmp in right limiter: %s\n", tmp);
    dprintf(2, "end in right limiter: %s\n", end); 
    
    if (*tmp == '"' || *tmp == '\'')
        tmp = remove_quote(tmp, ft_strlen(tmp) - 1);
    
    
    dprintf(2, "redirect in right limiter: %s\n", tmp);
    return (tmp);
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
    process->here_doc = right_delimiter(redirect, process);//delimiter: end

    dprintf(2, "process->here_doc: %s\n", process->here_doc);
    close(ms->fd[0]);
    heredoc_fd = open(heredoc_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
    
    if (heredoc_fd == -1)
    {
        //close_fd
        //print_error
        perror("open .heredoc failed");
        return(set_exitcode(ms, 1)); 
    }
    get_heredoc_input(heredoc_fd, process);
    if (close(heredoc_fd) == -1)
    {
        //close_fd(ms)
        //print_error
        perror("open .heredoc failed");
        return(set_exitcode(ms, 1)); 
    }
    ms->fd[0] = open(heredoc_name, O_RDONLY);
    if (ms->fd[1] == -1)
    {
        //close_fd(ms)
        //print_error
        perror("open .heredoc failed");
        return(set_exitcode(ms, 1)); 
    }
    
    unlink(heredoc_name);
    free(heredoc_name);
    return (0);
}