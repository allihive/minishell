/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:14:29 by alli              #+#    #+#             */
/*   Updated: 2023/11/13 15:23:27 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		strlen;

	strlen = ft_strlen(src);
	dest = malloc(sizeof(char) * (strlen + 1));
	if (dest == '\0')
		return (0);
	ft_strlcpy(dest, src, strlen + 1);
	return (dest);
}
