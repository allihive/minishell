/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:07:06 by alli              #+#    #+#             */
/*   Updated: 2024/08/13 16:36:13 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_redir_err(t_shell *ms, char *redir, char *copy)
{
	if (*redir == '/')
		error_msg(redir, 0, "Is a directory", ms->excode = 126);
	else if (ft_strchr(copy, '\"'))
		error_msg(redir, 0, "No such file or directory", ms->excode = 1);
	else
		error_msg(redir, 0, "No such file or directory", ms->excode = 1);
	ms->excode = 0;
	return (-1);
}

int	expand_redir_in(t_shell *ms, char *redirect, int j)
{
	int		i;
	char	*tmp;
	char	*copy;

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
	ms->list->redirect_in[j] = tmp;
	free(copy);
	return (0);
}

int	validate_redir_in(t_process_node *mod, t_shell *ms, char *redirect, int j)
{
	//char	*tmp;

	if (ft_strchr(redirect, '$'))
	{
		if (expand_redir_in(ms, redirect, j))
			return (set_exitcode(ms, 1));
	}
	else
	{
		//tmp = redirect;
		mod->redirect_in[j] = quote_remover(redirect);
		if (!redirect)
			return (set_exitcode(ms, -1));
	}
	return (0);
}
