/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:29:14 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/31 13:33:33 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern volatile sig_atomic_t global_signal; 

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

//int g_signal = 0; //global variable

typedef struct s_process_node//
{
	char **command;
	char *node_line;// = input
	
	char	**redirs;
	
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

/*signals*/
void	set_termios(int mode);
void	set_signal(void);
void	sig_ctrl_c(int sig);
// void	signal_heredoc(int sig);
void	ctrl_c_heredoc(int sig);

/*Initialization*/
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
void	env(t_shell *ms, int fd);
void	pwd(t_shell *ms, char **cmd, int fd);
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
int ifisredirect(char c);
void parse_process_node(t_process_node **list, t_shell *ms);


/*Expand*/
char *expand_it_out(char *cmd, t_process_node *mod, t_shell *ms);
char	*find_value(t_shell *ms, char *key);
char 	*find_key_in_envp(t_shell *ms, char *key);
char *quote_remover(char *str);
int count_quote(char *str);
char *remove_quote(char *str, int len);

/*error handling*/
void	error_handle(t_shell *ms);
void	only_print_error(char *name);
void	error_msg(char *cmd, char *str, char *msg);
void	heredoc_input_msg(char *str);

/*free*/
void	free_single(char *str);
void	free_double(char **arr);
void free_node(t_process_node **lst);
void free_shell(t_shell *ms);
int close_and_free(t_shell *ms);
int free_env(t_shell *ms);

/*Builtin utils*/
_Bool	is_builtin(char *cmd);
_Bool	check_case(char *cmd, char *builtin);

/* Pipex*/
int pipex(t_process_node *process, t_shell *ms);
int check_cmd(char *str);
int wait_children(t_shell *ms, int *pids, int count);

/*Fd*/
int get_fd(char *input, t_process_node *process, t_shell *ms);

/*Execution*/
int do_process(t_process_node *process,t_shell *ms);
int	call_builtin(t_shell *ms, t_process_node *node);

/*get redirect*/
void get_redirect_arr(char *input, t_process_node *mod, t_shell *ms);;

/*Redirects*/
//int handle_redirects(t_process_node *process,t_shell *ms);
char	*check_redirect( char *redirect, t_process_node *mod, t_shell *ms);
int redir_out(char *redirectout, t_shell *ms, int i);
//int redir_out(char *redirectout, t_shell *ms);
int redir_append(char *redirectappend, t_shell *ms);
int go_check_redirect(char *input, t_process_node *mod, t_shell *ms);

/*Redirects utils*/
int validate_redir_in(t_shell *ms, char *redirect, int j);
//int redir_in(char *redirectin,t_shell *ms);
int redir_in(char *redirectin,t_shell *ms, int j);
int	print_redir_err(t_shell *ms, char *redir, char *copy);
int validate_redir_out(t_shell *ms, char *redirect, int i);

/*Handle exitcode*/
int	set_exitcode(t_shell *ms, int exitcode);


/*parsing*/
char *check_if_quote(char *str);

/*Utils*/
int ifisspace(char c);


/*Heredoc*/
int handle_heredocs(char *redirect, t_process_node *process,t_shell *ms);
//int handle_heredocs(char *redirect, t_process_node *process);
#endif