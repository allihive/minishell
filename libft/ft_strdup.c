/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:14:29 by alli              #+#    #+#             */
/*   Updated: 2024/06/27 11:52:07 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		strlen;

	strlen = ft_strlen(src);
	dest = malloc(sizeof(char) * (strlen + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, src, strlen + 1);
	return (dest);
}
