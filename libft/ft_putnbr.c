/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:40:53 by alli              #+#    #+#             */
/*   Updated: 2023/11/29 08:55:48 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long f)
{
	int		i;
	char	*symbols;

	symbols = "0123456789";
	if (f < 0)
	{
		if (write (1, "-", 1) < 0)
			return (-1);
		return (ft_putnbr(-f) + 1);
	}
	else if (f < 10)
	{
		return (ft_putchar(symbols[f]));
	}
	else
	{
		i = ft_putnbr(f / 10);
		if (i < 0)
			return (-1);
		return (i + ft_putnbr(f % 10));
	}
}

int	ft_putnbr_u(unsigned int u)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	if (u < 10)
	{
		u = u + '0';
		i += ft_putchar(u);
		if (i == -1)
			return (-1);
	}
	else
	{
		temp = ft_putnbr(u / 10);
		if (temp < 0)
			return (-1);
		i += temp;
		i += ft_putchar((u % 10) + '0');
		if (i == -1)
			return (-1);
	}
	return (i);
}

int	ft_hexnum_l(unsigned int n)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	if (n > 15)
	{
		i = ft_hexnum_l(n / 16);
		temp = i;
		if (temp < 0)
			return (-1);
	}
	i += ft_putchar("0123456789abcdef"[n % 16]);
	if (i < 0)
		return (-1);
	return (i);
}

int	ft_hexnum_u(unsigned int n)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	if (n > 15)
	{
		i = ft_hexnum_u(n / 16);
		temp = i;
		if (temp < 0)
			return (-1);
	}
	i += ft_putchar("0123456789ABCDEF"[n % 16]);
	if (i < 0)
		return (-1);
	return (i);
}
