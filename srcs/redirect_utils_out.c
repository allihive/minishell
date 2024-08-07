/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:33:41 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/06 13:27:31 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_redir_out(t_shell *ms, char *redirect, int j)
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
    ms->list->redirect_out[j] = quote_remover(redirect);
    
    while (redirect[i] == '<' || redirect[i] == '>')
        i++;
    if (!redirect[i] || redirect[i] == '/')
    {
        print_redir_err(ms, redirect + 1, &copy[i]);
        free(copy);
        return (-1);
    }
	free (tmp);
    free(copy);
    return (0);
}


int validate_redir_out(t_shell *ms, char *redirect, int j)//$USER
{
    char *tmp;

    if (ft_strchr(redirect, '$'))
    {
        if (expand_redir_out(ms, redirect, j))
            return (set_exitcode(ms, 1));
    }
    else
    {
        tmp = redirect;
        ms->list->redirect_out[j] = quote_remover(redirect);
        //free(tmp);
        if (!redirect)
            return (set_exitcode(ms, -1));
    }
    return (0);
}