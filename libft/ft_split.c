/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:56:34 by alli              #+#    #+#             */
/*   Updated: 2023/11/15 14:32:40 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (words);
}

static char	**ft_free(char **split, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	*word_copy(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((sizeof(char)) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	char	**split;
	int		array_pos;

	i = -1;
	split = malloc((count_words(s, c) + 1) * sizeof (char *));
	if (!s || !split)
		return (0);
	j = 0;
	array_pos = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && array_pos < 0)
			array_pos = i;
		else if ((s[i] == c || i == ft_strlen(s)) && array_pos >= 0)
		{
			split[j] = word_copy(s, array_pos, i);
			if (!split[j++])
				return (ft_free(split, j));
			array_pos = -1;
		}
	}
	split[j] = 0;
	return (split);
}
