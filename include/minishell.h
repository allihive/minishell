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
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

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

typedef struct s_heredoc
{
	char	*dlm;
	char	*line;
	int		dlm_len;
	int		fd;
}	t_heredoc;

typedef struct s_flags
{
	int	in_single;
	int	in_double;
}	t_flags;

// int	g_signal = 0;

typedef struct s_process_node
{
	char **command;
	char *node_line;// = input
	char **redirect_in;//< input
	char **redirect_out;//> output
	char *here_doc;//<<
	char *append_s;//>>
	char	*cmd_path;
	int pipe;
	int sinquote;//when ==1 dont exapmd unless expand == 1;
	int doublequote;
	int append;//append
	int heredoc;
	int redirectin;
	int redirectout;
	int		meta;
	int		process_mode;
	int			builtin;
	int expand;
	
	struct 	s_process_node *next;
}	t_process_node;

// typedef	struct s_envp
// {
// 	char	*key;
// 	char	*value;
// 	struct	s_envp	*next;
// }	t_envp;

typedef struct s_shell //ms
{
	char 	**envp;
	int 	envp_size;
	char	**envp_paths;
	int 	shlvl;//? not sure if we need this
	char	*line;// read from realine function
	int		fork_n;//fork number
	int fd[2];
	int read_end;
	char *cwd;
	int excode;
	int	execute;
	pid_t *pids;
	int	 count;//node index  在pipex 會update
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
void	cd(t_shell *ms, char **cmd, char *pwd, char *oldpwd);
int	cmd_counter(char **cmd);

/*Export Builtin Functions*/
// int		export_str_check(char *str);
int		ft_export(t_shell *ms, char **cmd, int fd);
void 	envp_add(t_shell *ms, char *name);
void	envp_print(t_shell *ms, int fd);
void 	envp_update(t_shell *ms, char *name);
char 	*env_exists(char *name, t_shell *ms);

// char 	*name_exists(t_shell *ms, char *name);
void	env(t_shell *ms, int fd);
void	pwd(t_shell *ms, char **cmd, int fd);
// void    envp_delete(t_shell *ms, char *name);
void	envp_remove(t_shell *ms, char *content);
void	unset(t_shell *ms, char **cmd);

/*Echo function*/
void	echo(t_shell *ms, char **output, int fd);
void	print_value(t_shell *ms, char *str);

/*Exit Function*/
int	ft_exit(t_shell *ms, char **cmd);

/*Parse Functions*/
int init_process_node(char *line, t_shell *ms);
void execute_shell(t_shell *ms);
int count_cmd(t_process_node *list);


/*expand*/
char *expand_it_out(char *cmd, t_process_node *mod, t_shell *ms);
char	*find_value(t_shell *ms, char *key);
char 	*find_key_in_envp(t_shell *ms, char *key);
char *quote_remover(char *str);
int count_quote(char *str);
char *remove_quote(char *str, int len);




/*error handling*/
void	error_handle(t_shell *ms);
void	only_print_error(char *name);

/*free*/
void	free_single(char *str);
void	free_double(char **arr);
void free_node(t_process_node **lst);

/*Builtin utils*/
_Bool	is_builtin(char *cmd);
_Bool	check_case(char *cmd, char *builtin);

/* Pipex*/
int pipex(t_process_node *process, t_shell *ms);
int check_cmd(char *str);
int wait_children(t_shell *ms, int *pids, int count);

/*Fd*/
char *get_fd(char *input, t_process_node *process, t_shell *ms);

/*Execution*/
int do_process(t_process_node *process,t_shell *ms);
int	call_builtin(t_shell *ms, t_process_node *node);


/*Redirects*/
//int handle_redirects(t_process_node *process,t_shell *ms);
char	*check_redirect( char *redirect, t_process_node *mod, t_shell *ms);
void redir_in(char *redirectin,t_shell *ms);
void redir_out(char *redirectout, t_shell *ms);
void redir_append(char *redirectappend, t_shell *ms);
char *go_check_redirect(char *input, t_process_node *mod, t_shell *ms);

/*Handle exitcode*/
int	set_exitcode(t_shell *ms, int exitcode);


/*Utils*/
int ifisspace(char c);

#endif