/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 08:58:52 by alli              #+#    #+#             */
/*   Updated: 2023/12/12 08:50:55 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	newline_check(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*join_strs(const char *s1, const char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	join = ft_zeromalloc(i + j + 1, sizeof(char));
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	return (join);
}

char	*ft_strdup(const char *s)
{
	char	*newstr;
	int		i;

	i = 0;
	if (!s)
		return (ft_strdup(""));
	while (s[i])
		i++;
	newstr = ft_zeromalloc(i + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = s[i];
		i++;
	}
	return (newstr);
}

void	*ft_zeromalloc(size_t count, size_t size)
{
	void	*s;
	size_t	i;
	char	*str;

	s = NULL;
	str = (char *) s;
	str = malloc(count * size);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (size * count))
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

void	ft_free_strs(char **str, char **str2, char **str3)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (str3 && *str3)
	{
		free(*str3);
		*str3 = NULL;
	}
}
