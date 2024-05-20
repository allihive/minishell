/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:49:59 by alli              #+#    #+#             */
/*   Updated: 2023/12/12 08:49:55 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

void	ft_free_strs(char **str, char **str2, char **str3);
char	*ft_parse_line(char **keep, char **tmp);
char	*ft_strdup(const char *s);
void	*ft_zeromalloc(size_t count, size_t size);
char	*get_after_nline(const char *s);
char	*get_before_nline(const char *s);
char	*get_next_line(int fd);
char	*join_strs(const char *s1, const char *s2);
int		newline_check(const char *s);
int		read_line(int fd, char **keep, char **tmp);

#endif
