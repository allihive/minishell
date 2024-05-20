/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:24:15 by alli              #+#    #+#             */
/*   Updated: 2023/11/15 15:44:14 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n <= 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	get_char(char *str, int n, int len)
{
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[len - 1] = '0' + n % 10;
		n = n / 10;
		(len)--;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_int_len(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	if (n == 0)
		str[len - 1] = '0';
	str[len] = '\0';
	if (n == -2147483648)
	{
		str[len - 1] = '8';
		n = -214748364;
		len--;
	}
	get_char(str, n, len);
	return (str);
}
