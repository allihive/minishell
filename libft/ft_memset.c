/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:38:19 by alli              #+#    #+#             */
/*   Updated: 2023/11/13 13:35:48 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*char_b;

	i = 0;
	char_b = (unsigned char *) b;
	while (i < len)
	{
		char_b[i] = (unsigned char)c;
		i++;
	}
	return (char_b);
}
