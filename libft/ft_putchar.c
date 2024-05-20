/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:43:54 by alli              #+#    #+#             */
/*   Updated: 2023/11/27 08:15:51 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;
	int	temp;

	i = 0;
	if (!s)
	{
		if (ft_putstr("(null)") == -1)
			return (-1);
		return (6);
	}
	while (s[i] != '\0')
	{
		temp = write(1, &s[i], 1);
		if (temp < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_ret_ptr(void *ptr)
{
	unsigned long	base;
	int				help;
	int				temp;

	base = (unsigned long) ptr;
	help = 0;
	temp = 0;
	if (ptr < 0)
		return (-1);
	if (base > 15)
	{
		temp = ft_ret_ptr((void *)(base / 16));
		help += temp;
	}
	if (ft_putchar("0123456789abcdef"[base % 16]) < 0)
		return (-1);
	help++;
	return (help);
}
