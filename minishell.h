#ifndef MINISHELL_H
# define MINISHELL_H
# define true  1
# define false 0

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <readline/readline.h>

typedef struct s_shell 
{
	char **env;
	int exit_code;
}	t_shell;

#endif