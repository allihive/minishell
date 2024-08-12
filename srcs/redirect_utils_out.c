/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:33:41 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/12 15:48:16 by alli             ###   ########.fr       */
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

int	validate_redir_out(t_process_node *mod, t_shell *ms, char *redirect, int j)
{
	char	*tmp;
	
	// printf("entered valiate j: %d\n", j);
	if (ft_strchr(redirect, '$'))
	{
		if (expand_redir_out(ms, redirect, j))
			return (set_exitcode(ms, 1));
	}
	else
	{
		//dprintf(2, "1 validate redi_out ms->list->redire_out:  %s\n", ms->list->redirect_out[j]);
		// dprintf(2, "1 validate redi_out redir:  %s\n", redirect);
		tmp = quote_remover(redirect); //ms->list->redirect_out[j]
		// printf("tmp in validate: %s\n", tmp);
		// printf("entered valiate j: %d,%p\n", j, mod->redirect_out);
		//printf("entered valiate j: %d,%p\n", j, ms->list->next->redirect_out);
		//ms->list->redirect_out[j] = tmp;
		mod->redirect_out[j] = tmp;
		// printf("mod->redirect_out[j] in validate: %s\n", mod->redirect_out[j]);
		//printf("validate redi_out ms->list->redire_out:  %s\n", ms->list->redirect_out[j]);
		if (!redirect)
			return (set_exitcode(ms, -1));
	}
	// printf("2 entered valiate redir_out redirect: %s\n", redirect);
	return (0);
}
