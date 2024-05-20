/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:45:14 by alli              #+#    #+#             */
/*   Updated: 2024/03/08 14:06:25 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char spec, va_list ap)
{
	if (spec == '%')
		return (ft_putchar('%'));
	else if (spec == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (spec == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (spec == 'd' || spec == 'i')
		return (ft_putnbr((long)va_arg(ap, int)));
	else if (spec == 'p')
	{
		if (ft_putstr("0x") < 0)
			return (-1);
		return (ft_ret_ptr(va_arg(ap, void *)) + 2);
	}
	else if (spec == 'u')
		return (ft_putnbr_u(va_arg(ap, unsigned int)));
	else if (spec == 'x')
		return (ft_hexnum_l(va_arg(ap, unsigned int)));
	else if (spec == 'X')
		return (ft_hexnum_u(va_arg(ap, unsigned int)));
	return (0);
}

int	ft_printf(const char *ap, ...)
{
	va_list	arg;
	int		i;

	va_start (arg, ap);
	i = 0;
	while (*ap != '\0')
	{
		if (*ap == '%')
		{
			i += print_format(*(ap + 1), arg);
			if (i < 0)
				return (-1);
			ap++;
		}
		else
		{
			if (write (1, ap, 1) < 0)
				return (-1);
			i++;
		}
		++ap;
	}
	va_end (arg);
	return (i);
}
