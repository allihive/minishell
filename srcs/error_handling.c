/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:45:25 by alli              #+#    #+#             */
/*   Updated: 2024/05/29 09:49:38 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handle(t_shell *ms)
{
	if (ms->envp)
	{
		ft_free_strs(ms->envp, 0, 0);
		free(ms);
		exit(ms->exit_code);
	}
	ft_printf("Readline unable to read");
	exit(ms->exit_code);
}