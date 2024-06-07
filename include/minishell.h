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

int	g_signal;
typedef struct s_process_node
{
	char **command; 
	/*
	echo
	hello $USER
	*/
	char *node_line;// = input
	char *redirect_in;//< input
	char *redirect_out;//> output
	char *heredoc;//<<
	char *append;//>>
	int fd_in;
	int fd_out;
	int pipe;
	int sinquote;//when ==1 dont exapmd unless expand == 1;
	int doublequote;
	int append;
	int heredoc;
	int		meta;
	int		process_mode;
	int expand;
	
	struct 	s_process_node *next;
}	t_process_node;


typedef struct s_shell 
{
	char **envp;
	int envp_size;
	int exit_code;
	int shlvl;//? not sure if we need this
	char	*line;// read from realine function
	int fork_n;//fork number
	pid_t *pids;
	t_process_node *list;//list
}	t_shell;

void	set_termios(int mode);
void	set_signal(void);
void	sig_ctrl_c(int sig);
void	init_envp(t_shell *ms, char **envp);
void	initialize_shell(t_shell *ms, char **envp);
int 	check_shlvl(t_shell *ms);

/*Builtin*/
void	execute_builtin(t_shell *ms);

/*Export Builtin Functions*/
int	export_str_check(char *str);
int	export(t_shell *ms, char *cmd);
void envp_add(t_shell *ms, char *name);
void envp_update(t_shell *ms, char *name);
char *env_exists(char *name, t_shell *ms);
char *name_exists(t_shell *ms, char *name);

/*Parse Functions*/
int init_process_node(char *line, t_shell *ms);

/*error handling*/
void	error_handle(t_shell *ms);

#endif