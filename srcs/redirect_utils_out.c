/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:33:41 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 12:45:06 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_redir_out(t_shell *ms, char *redirect, int j)
{
	int		i;
	char	*tmp;
	char	*copy;

	i = 0;
	copy = ft_strdup(redirect);
	if (!copy)
		return (set_exitcode(ms, -1));
	redirect = expand_it_out(redirect, ms->list, ms);
	ms->list->redirect_out[j] = quote_remover(redirect);
	tmp = ms->list->redirect_out[j];
	while (tmp[i] == '<' || tmp[i] == '>')
		i++;
	if (!tmp[i] || tmp[i] == '/')
	{
		print_redir_err(ms, tmp + 1, &copy[i]);
		free(copy);
		return (-1);
	}
	ms->list->redirect_out[j] = tmp;
	free(copy);
	return (0);
}

int	validate_redir_out(t_process_node *mod,
	t_shell *ms, char *redirect, int j)
{
	char	*tmp;

	if (ft_strchr(redirect, '$'))
	{
		if (expand_redir_out(ms, redirect, j))
			return (set_exitcode(ms, 1));
	}
	else
	{
		tmp = quote_remover(redirect);
		mod->redirect_out[j] = tmp;
		if (!redirect)
			return (set_exitcode(ms, -1));
	}
	return (0);
}
