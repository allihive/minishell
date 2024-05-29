#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdio.h>
# include <termios.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>


# define true  1
# define false 0

typedef struct s_shell 
{
	char **envp;
	int envp_size;
	int exit_code;
}	t_shell;

void	set_termios(int mode);
void	set_signal(int sig);
void	sig_ctrl_c(int sig);
void	init_envp(t_shell *ms, char **envp);
void	initialize_shell(t_shell *ms, char **envp);

/*error handling*/
void	error_handle(t_shell *ms);

#endif