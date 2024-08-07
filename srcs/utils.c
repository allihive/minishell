/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:52:02 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/07 17:52:24 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*echo_exit_code(t_shell *ms)
{
	char *exit_code;

	//printf("in echo_exit %d\n", ms->excode);
	exit_code = ft_itoa(ms->excode);
	if (!exit_code)
		return (NULL);
	return (exit_code);
}
