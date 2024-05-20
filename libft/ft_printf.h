/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:23:39 by alli              #+#    #+#             */
/*   Updated: 2023/11/29 10:33:47 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_putchar(char c);
int		ft_putnbr(long f);
int		ft_printf(const char *ap, ...);
int		ft_ret_ptr(void *ptr);
int		ft_putstr(char *s);
int		ft_putnbr_u(unsigned int u);
int		ft_hexnum_l(unsigned int n);
int		ft_hexnum_u(unsigned int n);
size_t	ft_strlen(const char *str);

#endif