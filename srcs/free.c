

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