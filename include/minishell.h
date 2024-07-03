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

typedef enum e_syntax
{
	PIPE = 124,
	//DOLLAR = 36,
	//INDIRECT = 60,
	//OUTDIRECT = 62,
	SINGLEQUOTE = 39,
	DOUBLEQUOTE = 34,
	//QUESTIONMARK = 63,
}	t_syntax;

// int	g_signal = 0;

typedef struct s_process_node
{
	char **command;
	char *node_line;// = input
	char **redirect_in;//< input
	char **redirect_out;//> output
	char *here_doc;//<<
	char *append_s;//>>
	int fd_in;
	int fd_out;
	int pipe;
	int sinquote;//when ==1 dont exapmd unless expand == 1;
	int doublequote;
	int append;//append
	int heredoc;
	int redirectin;
	int redirectout;
	int		meta;
	int		process_mode;
	int expand;
	
	struct 	s_process_node *next;
}	t_process_node;

// typedef	struct s_envp
// {
// 	char	*key;
// 	char	*value;
// 	struct	s_envp	*next;
// }	t_envp;

typedef struct s_shell 
{
	char 	**envp;
	int 	envp_size;
	int 	exit_code;
	int 	shlvl;//? not sure if we need this
	char	*line;// read from realine function
	int		fork_n;//fork number
	// char	*cwd;
	int	excode;
	char *cwd;
	int exitcode;
	pid_t *pids;
	int	 index;
	t_process_node *list;//list
	// t_envp	*envp_list;
}	t_shell;

void	set_termios(int mode);
void	set_signal(void);
void	sig_ctrl_c(int sig);
void	init_envp(t_shell *ms, char **envp);
void	initialize_shell(t_shell *ms, char **envp);
int 	add_shlvl(t_shell *ms);

/*Builtin*/
void	execute_builtin(t_shell *ms, t_process_node *node);

/*Export Builtin Functions*/
// int		export_str_check(char *str);
int		ft_export(t_shell *ms, char **cmd);
void 	envp_add(t_shell *ms, char *name);
void	envp_print(t_shell *ms);
void 	envp_update(t_shell *ms, char *name);
char 	*env_exists(char *name, t_shell *ms);
// char 	*name_exists(t_shell *ms, char *name);
void	env(t_shell *ms);
void	pwd(t_shell *ms, char **cmd);
// void    envp_delete(t_shell *ms, char *name);
void	envp_remove(t_shell *ms, char *content);
void	unset(t_shell *ms, char **cmd);

/*Echo function*/
void	echo(t_shell *ms, char **output);
void	print_value(t_shell *ms, char *str);

/*Exit Function*/
void	ft_exit(t_shell *ms, char **cmd);

/*Parse Functions*/
int init_process_node(char *line, t_shell *ms);
void execute_shell(t_shell *ms);
int count_cmd(t_process_node *list);

/*expand*/
char *expand_it_out(char *cmd, t_process_node *mod, t_shell *ms);
char	*find_value(t_shell *ms, char *key);
int	find_key_in_envp(t_shell *ms, char *key);

/*error handling*/
void	error_handle(t_shell *ms);

/*free*/
void	free_single(char *str);
void	free_double(char **arr);
#endif