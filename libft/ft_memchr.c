/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:36:11 by alli              #+#    #+#             */
/*   Updated: 2023/11/15 16:21:50 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			j;

	j = 0;
	str = (unsigned char *) s;
	while (j < n)
	{
		if (str[j] == (unsigned char)c)
			return (str + j);
		j++;
	}
	return (0);
}
