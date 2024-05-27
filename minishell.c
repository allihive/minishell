/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:01:45 by alli              #+#    #+#             */
/*   Updated: 2024/05/27 15:33:02 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(t_shell *ms)
{
	
}

int	main(int argc, char **argv)
{
	char *line;
	t_shell ms;

	initialize_shell(&ms);
	while (true)
	{
		line = readline("lobster-shell 🦞: ");
		if (!line)
			error_handle(ms);
		else
		{
			add_history(line);
			free(line);
		}
	}
	return (0);
}