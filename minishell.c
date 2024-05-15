#include "minishell.h"

int	main(int argc, char **argv)
{
	char *line;

	while (1)
	{
		line = readline("lobster-shell 🦞: ");
		// line = NULL;
		if (!line)
		{
			printf("no readline");
			return (1);
		}
		//put the signals here?
		else
		{
			add_history(line);
			free(line);
		}
	}
	return (0);
}