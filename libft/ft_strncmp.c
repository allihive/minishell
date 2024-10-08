/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:13:26 by alli              #+#    #+#             */
/*   Updated: 2024/08/08 16:18:00 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	i = 0;
// 	str1 = (unsigned char *) s1;
// 	str2 = (unsigned char *) s2;
// 	while ((str1[i] && str2[i]) && (i < n))
// 	{
// 		if (str1[i] - str2[i] != 0)
// 		{
// 			return (str1[i] - str2[i]);
// 		}
// 		i++;
// 	}
// 	if (i != n)
// 	{
// 		return (str1[i] - str2[i]);
// 	}
// 	return (0);
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n-- != 0)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		++s1;
		++s2;
	}
	return (0);
}
