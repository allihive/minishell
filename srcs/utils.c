/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:52:02 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/09 12:41:33 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*echo_exit_code(t_shell *ms)
{
	char	*exit_code;

	exit_code = ft_itoa(ms->excode);
	if (!exit_code)
		return (NULL);
	return (exit_code);
}

void	quit(t_shell *ms)
{
	ft_putstr_fd("exit\n", 2);
	free_env(ms);
	exit(0);
}
