/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:27:34 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/05 20:27:39 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_single(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

void	free_double(char **arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
		free_single(arr[i++]);
	free(arr);
	arr = NULL;
}


//free_env(ms)

//close_and_free