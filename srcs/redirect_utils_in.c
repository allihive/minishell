
#include "minishell.h"

int	print_redir_err(t_shell *ms, char *redir, char *copy)
{
	if (*redir == '/')// /
		//printf("shell: %s: Is a directory\n", redir);//need change to erro message
		error_msg(redir, 0, "Is a directory", ms->excode = 126);
	else if (ft_strchr(copy, '\"'))// cat \"
		//printf("shell: : No such file or directory\n");//need change to erro message
		error_msg(redir, 0, "No such file or directory", ms->excode = 1);
	else
		//printf( "shell: %s: ambiguous redirect\n", copy);//need change to erro message
		error_msg(redir, 0, "No such file or directory", ms->excode = 1);
	ms->excode = 0;
	return (-1);
}


int	expand_redir_in(t_shell *ms, char *redirect, int j)
{
    int i;
    char *tmp;
    char *copy;

    i = 0;
    copy = ft_strdup(redirect);
	if (!copy)
    	return (set_exitcode(ms, -1));
	redirect = expand_it_out(redirect, ms->list, ms);
    
    ms->list->redirect_in[j] = quote_remover(redirect);
	tmp = ms->list->redirect_in[j];
    while (tmp[i] == '<' || tmp[i] == '>')
        i++;
    if (!tmp[i] || tmp[i] == '/')
    {
        print_redir_err(ms, tmp + 1, &copy[i]);
        free(copy);
        return (-1);
    }
    ms->list->redirect_in[j] = tmp;;
	//free (tmp);
	free(copy);
    return (0);
}


int validate_redir_in(t_shell *ms, char *redirect, int j)//$USER
{
    char *tmp;

    if (ft_strchr(redirect, '$'))
    {
        if (expand_redir_in(ms, redirect, j))
            return (set_exitcode(ms, 1));
    }
    else
    {
        tmp = redirect;
        ms->list->redirect_in[j] = quote_remover(redirect);
        //free(tmp);
        if (!redirect)
            return (set_exitcode(ms, -1));
    }
    return (0);
}