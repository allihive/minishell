/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@hive.student.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:52:22 by alli              #+#    #+#             */
/*   Updated: 2024/06/11 15:50:38 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	ln;

	if (!s)
		return (NULL);
	ln = ft_strlen(s);
	if (!*s || start >= ln)
		return ((ft_strdup("")));
	if (len > ln - start)
		len = ln - start;
	new = ft_calloc(len + 1, sizeof(char));
	if (new)
		ft_strlcpy(new, s + start, len + 1);
	return (new);
}
