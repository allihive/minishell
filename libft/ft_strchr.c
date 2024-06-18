/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:25:25 by alli              #+#    #+#             */
/*   Updated: 2024/06/18 16:03:23 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	// int		i;
	char	*str;

	// i = 0;
	str = (char *) s;
	while (*str != (char)c)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return (str);
}
