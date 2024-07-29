
#include "minishell.h"

int	print_redir_err(t_shell *ms, char *redir, char *copy)
{
	if (*redir == '/')
		printf("shell: %s: Is a directory\n", redir);//need change to erro message
	else if (ft_strchr(copy, '\"'))
		printf("shell: : No such file or directory\n");//need change to erro message
	else
		printf( "shell: %s: ambiguous redirect\n", copy);//need change to erro message
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
    tmp = redirect;
    ms->list->redirect_in[j] = quote_remover(redirect);
    free (tmp);
    while (redirect[i] == '<' || redirect[i] == '>')
        i++;
    if (!redirect[i] || redirect[i] == '/')
    {
        print_redir_err(ms, redirect + 1, &copy[i]);
        free(copy);
        return (-1);
    }
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
        free(tmp);
        if (!redirect)
            return (set_exitcode(ms, -1));
    }
    return (0);
}