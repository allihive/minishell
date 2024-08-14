/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:29:00 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 11:22:58 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_heredoc(char *line, char *delimiter,
	int stdin_backup, int heredoc_fd)
{
	if (line == NULL)
	{
		if (g_global_signal == 2)
		{
			dup2(stdin_backup, STDIN_FILENO);
			g_global_signal = 0;
			return (0);
		}
		heredoc_input_msg(delimiter);
		return (0);
	}
	if (ft_strncmp(line, delimiter, (ft_strlen(delimiter) + 1)) == 0)
	{
		free(line);
		return (0);
	}
	if (ft_putstr_fd(line, heredoc_fd) == -1)
	{
		if (line)
			free(line);
		line = NULL;
		free(delimiter);
		delimiter = NULL;
	}
	return (1);
}

void	get_heredoc_input(int heredoc_fd, t_process_node *process)
{
	char	*line;
	char	*delimiter;
	int		stdin_backup;

	line = NULL;
	delimiter = NULL;
	stdin_backup = dup(STDIN_FILENO);
	heredoc_init();
	delimiter = process->here_doc;
	if (!delimiter)
		return ;
	line = readline("> ");
	while (1)
	{
		if (output_heredoc(line, delimiter, stdin_backup, heredoc_fd) == 0)
			return ;
		if (line)
			free(line);
		line = readline("> ");
		write (heredoc_fd, "\n", 1);
	}
	dup2(stdin_backup, STDIN_FILENO);
	g_global_signal = 0;
	return ;
}

int	right_delimiter(char *redirect, t_process_node *process)
{
	char	*end;
	char	*tmp;
	char	*t_heredoc;

	while (ifisspace(*redirect))
		redirect++;
	end = redirect;
	tmp = redirect;
	while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
	if (process->here_doc == NULL)
	{
		process->here_doc = calloc(100, sizeof(char *));
		if (process->here_doc == NULL)
			return (perror("heredoc in malloc"), 1);
	}
	tmp = ft_substr(redirect, 0, end - tmp);
	if (!tmp)
		return (perror("heredoc in malloc"), 1);
	if (*tmp == '"' || *tmp == '\'')
		tmp = remove_quote(tmp, ft_strlen(tmp) - 1);
	t_heredoc = process->here_doc;
	process->here_doc = tmp;
	free(t_heredoc);
	return (0);
}

int	open_close_heredoc(char *heredoc_name, t_process_node *process, t_shell *ms)
{
	int	heredoc_fd;

	heredoc_fd = open(heredoc_name, O_CREAT
			| O_RDWR | O_TRUNC | O_APPEND, 0777);
	if (heredoc_fd == -1)
	{
		perror("open .heredoc failed");
		return (set_exitcode(ms, 1));
	}
	get_heredoc_input(heredoc_fd, process);
	if (close(heredoc_fd) == -1)
	{
		perror("open .heredoc failed");
		return (set_exitcode(ms, 1));
	}
	ms->fd[0] = open(heredoc_name, O_RDONLY);
	if (ms->fd[1] == -1)
	{
		perror("open .heredoc failed");
		return (set_exitcode(ms, 1));
	}
	return (0);
}

int	handle_heredocs(char *redirect, t_process_node *process, t_shell *ms)
{
	static int	i;
	char		*heredoc_name;

	i = 0;
	process->heredoc = i;
	i++;
	heredoc_name = ".heredoc";
	redirect += 2;
	if (right_delimiter(redirect, process))
	{
		perror("open .heredoc failed");
		return (set_exitcode(ms, 1));
	}
	close(ms->fd[0]);
	open_close_heredoc(heredoc_name, process, ms);
	unlink(heredoc_name);
	return (0);
}
