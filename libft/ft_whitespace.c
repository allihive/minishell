/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:12:56 by alli              #+#    #+#             */
/*   Updated: 2024/05/20 16:34:34 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_whitespace(char c)
{
	if (c == '\t'|| c == '\r' || c == '\n'
		|| c == ' ' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}
//should we skip a the white spaces in this function?