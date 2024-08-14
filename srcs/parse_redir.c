/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:08:08 by alli              #+#    #+#             */
/*   Updated: 2024/08/14 10:12:00 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redir_quote(char *tmp, int *quote_status)
{
	int	l;
	int	quote;

	quote = -1;
	l = 0;
	while (tmp[l])
	{
		if (tmp[l] == DOUBLEQUOTE && quote == -1)
			quote = DOUBLEQUOTE;
		else if (tmp[l] == DOUBLEQUOTE && quote == DOUBLEQUOTE)
			quote = -1;
		else if (tmp[l] == SINGLEQUOTE && quote == -1)
			quote = SINGLEQUOTE;
		else if (tmp[l] == SINGLEQUOTE && quote == SINGLEQUOTE)
			quote = -1;
		l++;
	}
	*quote_status = quote;
}

int	redirect_not_in_quote(char c, char *input, int k, t_shell *ms)
{
	int		quote_status;
	char	*tmp;

	if (c == '<' || c == '>')
	{
		tmp = ft_substr(input, 0, k);
		check_redir_quote(tmp, &quote_status);
		free (tmp);
		if (quote_status != -1)
			return (0);
		else
		{
			ms->execute = -1;
			return (1);
		}
	}
	else
		return (0);
}
