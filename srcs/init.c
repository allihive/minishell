/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:46:29 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 15:28:32 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quote(char *line)
{
	char	delim;

	while (line)
	{
		delim = check_delimiter(line);
		if (!delim)
			return (0);
		line = ft_strchr(line, delim);
		if (!ft_strchr(line + 1, delim))
			return (delim);
		line = ft_strchr(line + 1, delim) + 1;
	}
	return (0);
}

int	check_syntax(char *line, t_shell *ms)
{
	char	quote;

	if (!line || !*line || *line == '|' || *(line + ft_strlen(line) - 1) == '|')
		return (syntax_error("`|'", ms));
	quote = unclosed_quote(line);
	if (quote == SINGLEQUOTE)
		return (syntax_error("`\''", ms));
	else if (quote == DOUBLEQUOTE)
		return (syntax_error("`\"'", ms));
	if (invalid_redirect(line, '>'))
		return (syntax_error("`>'", ms));
	else if (invalid_redirect(line, '<'))
		return (syntax_error("`<'", ms));
	return (0);
}

void	init_node(t_process_node *new, char *line, char *temp)
{
	new->append = -1;
	new->heredoc = -1;
	new->expand = -1;
	new->doublequote = -1;
	new->sinquote = -1;
	new->redirectin = -1;
	new->redirectout = -1;
	new->command = NULL;
	new->node_line = NULL;
	new->redirect_in = NULL;
	new->redirect_out = NULL;
	new->append_s = NULL;
	new->here_doc = NULL;
	new->cmd_path = NULL;
	new->node_line = ft_substr(line, 0, (temp - line));
	if (!new->node_line)
		free(new->node_line);
}

int	init_shell(t_shell *ms)
{
	ms->count = 0;
	ms->read_end = -1;
	ms->fd[0] = dup(0);
	ms->fd[1] = dup(1);
	ms->fork_n = count_cmd(ms->list);
	ms->pids = ft_calloc((ms->fork_n + 1), sizeof(int));
	if (!ms->pids)
		return (close_and_free(ms));
	ms->pids[0] = -1;
	ms->execute = 0;
	return (0);
}

int	init_process_node(char *line, t_shell *ms)
{
	t_process_node	*new;
	char			*temp;

	if (!line || !*line || check_syntax(ms->line, ms) || empty_prompt(line))
		return (1);
	while (*line)
	{
		while (ifisspace(*line))
			line++;
		temp = point_end(line);
		new = ft_calloc(1, sizeof(t_process_node));
		if (!new)
			error_handle(ms, line);
		init_node(new, line, temp);
		append_process_node(&ms->list, new);
		check_syntax(new->node_line, ms);
		line = temp;
		if (*line)
			line++;
	}
	init_shell(ms);
	return (0);
}
