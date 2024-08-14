/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_append.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:11:15 by alli              #+#    #+#             */
/*   Updated: 2024/08/14 10:01:45 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_redir_append(t_shell *ms, char *redirect, int j)
{
	int		i;
	char	*tmp;
	char	*copy;

	i = 0;
	copy = ft_strdup(redirect);
	if (!copy)
		return (set_exitcode(ms, -1));
	redirect = expand_it_out(redirect, ms->list, ms);
	ms->list->append_s[j] = quote_remover(redirect);
	tmp = ms->list->append_s[j];
	while (tmp[i] == '<' || tmp[i] == '>')
		i++;
	if (!tmp[i] || tmp[i] == '/')
	{
		print_redir_err(ms, tmp + 1, &copy[i]);
		free(copy);
		return (-1);
	}
	ms->list->append_s[j] = tmp;
	free(copy);
	return (0);
}

int	validate_redir_append(t_process_node *mod,
	t_shell *ms, char *redirect, int j)
{
	char	*tmp;

	if (ft_strchr(redirect, '$'))
	{
		if (expand_redir_append(ms, redirect, j))
			return (set_exitcode(ms, 1));
	}
	else
	{
		tmp = quote_remover(redirect);
		if (!redirect)
			return (set_exitcode(ms, -1));
		mod->append_s[j] = tmp;
	}
	return (0);
}
