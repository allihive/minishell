/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:41:29 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/09 13:01:44 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_append(char *redirectappend, t_shell *ms, int j)
{
	int	i;

	i = 0;
	while (ifisspace(*redirectappend))
		redirectappend++;
	if (validate_redir_append(ms, redirectappend + i, j) == -1)
		return (-1);
	close(ms->fd[1]);
	if (ms->list->append == 1)
		ms->fd[1] = open(ms->list->append_s[j],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (ms->fd[1] < 0)
	{
		if (access(ms->list->append_s[j], F_OK) != 0)
			ft_printf("shell: %s: No such file or directory\n",
				redirectappend);//need to fix fd 2
		else
			ft_printf("shell: %s: Permission denied\n",
				redirectappend);//need to fix fd 2
		close_and_free(ms);
		return (set_exitcode(ms, -1));
	}
	return (0);
}

int	redir_out(char *redirectout, t_shell *ms, int j)
{
	int	i;

	i = 0;
	while (ifisspace(redirectout[i]) == 1)
		i++;
	if (validate_redir_out(ms, redirectout + i, j) == -1)
		return (-1);
	close(ms->fd[1]);
	if (redirectout)
		ms->fd[1] = open(ms->list->redirect_out[j],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ms->fd[1] < 0)
	{
		if (access(ms->list->redirect_out[j], F_OK) != 0)
			ft_printf("shell: %s: No such file or directory\n",
				redirectout);//need to fix fd 2
		else
			ft_printf("shell: %s: Permission denied\n",
				redirectout);//need to fix fd 2
		return (set_exitcode(ms, -1));
	}
	return (0);
}

int	redir_in(char *redirectin, t_shell *ms, int j)
{
	if (validate_redir_in(ms, redirectin, j) == -1)
		return (-1);
	close(ms->fd[0]);
	ms->fd[0] = open(ms->list->redirect_in[j], O_RDONLY);
	if (ms->fd[0] < 0)
	{
		if (access(ms->list->redirect_in[j], F_OK) != 0)
			error_msg(ms->list->redirect_in[j], 0,
				"No such infile or directory", ms->excode = 1);
		else
			error_msg(ms->list->redirect_in[j], 0,
				"Permission denied", ms->excode = 1);
		ms->execute = 0;
		return (set_exitcode(ms, -1));
	}
	return (0);
}
