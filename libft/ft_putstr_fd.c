/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:06:48 by alli              #+#    #+#             */
/*   Updated: 2024/06/27 11:53:23 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	// size_t	i;

	// i = 0;
	if (! s)
	{
		//if (ft_putstr_fd("(null)", fd) == -1)
			//return (-1);
		return (0);
	}
	if (write (fd, s, ft_strlen(s)) == -1)
		return (-1);
	return (0);
}
