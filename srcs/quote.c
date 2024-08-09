/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:49:02 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/09 13:19:19 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_flag(t_flags *f)
{
	f->in_single = -1;
	f->in_double = -1;
}

char	*remove_quote(char *str, int len)
{
	char	*new_str;
	int		i;
	int		j;
	t_flags	f;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	init_flag(&f);
	new_str = ft_calloc(len, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && f.in_double == -1)
			f.in_single *= -1;
		else if (str[i] == '"' && f.in_single == -1)
			f.in_double *= -1;
		else
			new_str[j++] = str[i];
		i++;
	}
	free(str);
	return (new_str);
}

int	count_quote(char *str)
{
	int		i;
	int		quote_n;
	t_flags	f;

	init_flag(&f);
	i = 0;
	quote_n = 0;
	while (str[i])
	{
		if (str[i] == '\'' && f.in_double == -1)
		{
			quote_n++;
			f.in_single *= -1;
		}	
		if (str[i] == '"' && f.in_single == -1)
		{
			quote_n++;
			f.in_double *= -1;
		}	
		i++;
	}
	return (quote_n);
}

char	*quote_remover(char *str)
{
	int	remove_q;
	int	len;

	remove_q = count_quote(str);
	len = ft_strlen(str) - remove_q + 1;
	return (remove_quote(str, len));
}

void	check_quote(t_process_node *mod, char c, int i)
{
	if (c == '\'' || c == '"')
	{
		if (mod->process_mode == 0)
		{
			if (c == '\'')
			{
				mod->process_mode = SINGLEQUOTE;
				mod->sinquote = i;
			}
			else
			{
				mod->process_mode = DOUBLEQUOTE;
				mod->doublequote = i;
			}
		}
		else if (c == '\'' && mod->process_mode == SINGLEQUOTE)
			mod->process_mode = 0;
		else if (c == '"' && mod->process_mode == DOUBLEQUOTE)
			mod->process_mode = 0;
	}
}
