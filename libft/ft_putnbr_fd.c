/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:40:53 by alli              #+#    #+#             */
/*   Updated: 2023/11/13 11:42:07 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int f, int fd)
{
	if (f == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (f < 0)
	{
		ft_putchar_fd('-', fd);
		f = -f;
	}
	if (f < 10)
	{
		f = f + '0';
		ft_putchar_fd(f, fd);
	}
	else
	{
		ft_putnbr_fd(f / 10, fd);
		ft_putchar_fd((f % 10) + '0', fd);
	}
}
