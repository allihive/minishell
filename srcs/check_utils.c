/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:29:42 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 15:30:59 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ifisredirect(char c)
{
	if ((c == '<' || c == '>'))
	{
		return (1);
	}
	return (0);
}

int	ifisspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ifismeta(char c)
{
	if (c == ';' || c == '$' || c == '\'' || c == '"')
		return (c);
	else
		return (0);
}

int	is_sep(char *str, int i, char *charset)
{
	int	j;
	int	k;
	int	flags;

	j = -1;
	while (charset[++j])
	{
		if (str[i] == charset[j])
		{
			k = -1;
			flags = 0;
			while (str[++k] && k <= i)
			{
				if (str[k] == '\\')
					flags ^= (1 << 2);
				if (str[k] == '"')
					flags ^= (1 << 1);
				if (str[k] == '\'')
					flags ^= 1;
			}
			return (flags == 0);
		}
	}
	return (str[i] == '\0');
}

char	*check_if_quote(char *str)
{
	int	k;

	k = 0;
	while (str[k])
	{
		if (ft_strlen(str) > 1)
		{
			if ((str[k] == '\''
					&& str[ft_strlen(str) - 1] == '\'')
				|| (str[k] == '"'
					&& str[ft_strlen(str) - 1] == '"'))
				str = no_quote(str);
		}
		k++;
	}
	return (str);
}
