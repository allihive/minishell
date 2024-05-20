/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:48:22 by alli              #+#    #+#             */
/*   Updated: 2024/01/12 09:31:04 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_after_nline(const char *s)
{
	char	*left;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j] != '\0')
		j++;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	left = ft_zeromalloc((j - i) + 1, sizeof(char));
	if (!left)
		return (NULL);
	j = 0;
	while (s[i + j])
	{
		left[j] = s[i + j];
		j++;
	}
	return (left);
}

char	*get_before_nline(const char *s)
{
	char	*line;
	int		i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\n')
		i++;
	line = ft_zeromalloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = s[i];
		i++;
	}
	return (line);
}

int	read_line(int fd, char **keep, char **tmp)
{
	char	*buf;
	int		r;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (ft_free_strs(&buf, keep, tmp), 0);
	r = 1;
	while (r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
			return (ft_free_strs(&buf, tmp, keep), 0);
		buf[r] = '\0';
		*tmp = ft_strdup(*keep);
		if (!*tmp)
			return (ft_free_strs(keep, tmp, &buf), 0);
		ft_free_strs(keep, 0, 0);
		*keep = join_strs(*tmp, buf);
		if (!*keep)
			return (ft_free_strs(keep, tmp, &buf), 0);
		ft_free_strs(tmp, 0, 0);
		if (newline_check(*keep))
			break ;
	}
	return (ft_free_strs(&buf, 0, 0), 0);
}

char	*ft_parse_line(char **keep, char **tmp)
{
	char	*line;

	*tmp = ft_strdup(*keep);
	if (!*tmp)
		return (NULL);
	ft_free_strs(keep, 0, 0);
	*keep = get_after_nline(*tmp);
	line = get_before_nline(*tmp);
	ft_free_strs(tmp, 0, 0);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*keep[1024];
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	tmp = NULL;
	line = NULL;
	read_line(fd, &keep[fd], &tmp);
	if (keep[fd])
		line = ft_parse_line(&keep[fd], &tmp);
	if (!line || *line == '\0')
	{
		ft_free_strs(&keep[fd], &line, &tmp);
		return (NULL);
	}
	return (line);
}
