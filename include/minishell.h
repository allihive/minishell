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

typedef struct s_process_node
{
	char **command;
	char *redirect_in;//< input
	char *redirect_out;//> output
	char *heredoc;//<<
	char *append;//>>
	int fd_in;
	int fd_out;
	int pipe;
	int sinquote;
	int doublequote;

	struct 	s_process_node *next;
}	t_process_node;


typedef struct s_shell 
{
	char **envp;
	int envp_size;
	int exit_code;
	char	*line;// read from realine function

}	t_shell;

void	set_termios(int mode);
void	set_signal(int sig);
void	sig_ctrl_c(int sig);
void	init_envp(t_shell *ms, char **envp);
void	initialize_shell(t_shell *ms, char **envp);

/*error handling*/
void	error_handle(t_shell *ms);

#endif