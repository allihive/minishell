/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:41:29 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 12:36:02 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_append(char *redirectappend, t_process_node *mod, t_shell *ms, int j)
{
	int	i;

	i = 0;
	while (ifisspace(*redirectappend))
		redirectappend++;
	if (validate_redir_append(mod, ms, redirectappend + i, j) == -1)
		return (-1);
	close(ms->fd[1]);
	if (mod->append == 1)
		ms->fd[1] = open(mod->append_s[j],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (ms->fd[1] < 0)
	{
		if (access(mod->append_s[j], F_OK) != 0)
			error_msg(mod->append_s[j], 0,
				"No such file or directory", ms->excode = 1);
		else
			error_msg(mod->append_s[j], 0,
				"No such file or directory", ms->excode = 1);
		return (-1);
	}
	return (0);
}

int	redir_out(char *redirectout, t_process_node *mod, t_shell *ms, int j)
{
	int	i;

	i = 0;
	while (ifisspace(redirectout[i]) == 1)
		i++;
	if (validate_redir_out(mod, ms, redirectout + i, j) == -1)
		return (-1);
	close(ms->fd[1]);
	if (redirectout)
		ms->fd[1] = open(mod->redirect_out[j],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ms->fd[1] < 0)
	{
		if (access(mod->redirect_out[j], F_OK) != 0)
			error_msg(mod->redirect_out[j], 0,
				"Permission denied", ms->excode = 1);
		else
			error_msg(mod->redirect_out[j], 0,
				"Permission denied", ms->excode = 1);
		return (-1);
	}
	return (0);
}

int	redir_in(char *redirectin, t_process_node *mod, t_shell *ms, int j)
{
	if (validate_redir_in(mod, ms, redirectin, j) == -1)
		return (-1);
	close(ms->fd[0]);
	ms->fd[0] = open(mod->redirect_in[j], O_RDONLY);
	if (ms->fd[0] < 0)
	{
		if (access(mod->redirect_in[j], F_OK) != 0)
			error_msg(mod->redirect_in[j], 0,
				"No such infile or directory", ms->excode = 1);
		else
			error_msg(mod->redirect_in[j], 0,
				"Permission denied", ms->excode = 1);
		ms->execute = 0;
		return (set_exitcode(ms, 1));
	}
	return (0);
}
