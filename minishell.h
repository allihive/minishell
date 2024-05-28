#ifndef MINISHELL_H
# define MINISHELL_H
# define true  1
# define false 0

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <termios.h>


typedef struct s_shell 
{
	char **env;
	int exit_code;
}	t_shell;

void	set_termios(int mode);
void	

#endif