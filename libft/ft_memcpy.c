/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:59 by alli              #+#    #+#             */
/*   Updated: 2023/11/15 16:33:54 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dest_ptr;
	char	*src_prt;

	i = 0;
	dest_ptr = (char *) dst;
	src_prt = (char *) src;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		dest_ptr[i] = src_prt[i];
		i++;
	}
	return (dest_ptr);
}
