/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/08 14:15:14 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	is_sep(char *str, int i, char *charset)
{
	int	j;
	int	k;
	int	flags;

	j = -1;
	while (charset[++j])
	{
		if (str[i] == charset[j])
		{
			k = -1;
			flags = 0;
			while (str[++k] && k <= i)
			{
				if (str[k] == '\\')
					flags ^= (1 << 2);
				if (str[k] == '"')
					flags ^= (1 << 1);
				if (str[k] == '\'')
					flags ^= 1;
			}
			return (flags == 0);
		}
	}
	return (str[i] == '\0');
}

static int	count_word(char *str, char *charset)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (!is_sep(str, i, charset)
			&& is_sep(str, i + 1, charset))
			word++;
		i++;
	}
	return (word);
}

static char	*write_word(char *dest, char *str, char *charset)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (is_sep(str, i, charset))
			i++;
		while (!is_sep(str, i, charset))
		{
			if (str[i] == '\\')
				i++;
			dest[j++] = str[i++];
		}
		break ;
	}
	dest[j] = '\0';
	return (dest);
}

static char	**write_arr(char **arr, char *str, char *charset)
{
	int	len;
	int	i;
	int	word;

	len = 0;
	i = 0;
	word = 0;
	while (str[i])
	{
		if (is_sep(str, i, charset))
			i++;
		else
		{
			while (!is_sep(str, i + len, charset))
				len++;
			arr[word] = malloc(sizeof(char) * (len + 1));
			if (arr[word] == NULL)
				return (NULL);
			arr[word] = write_word(arr[word], str + i, charset);
			i += len;
			len = 0;
			word++;
		}
	}
	
	return (arr);
}

/* 
	A customized ft_split() function, which splits the string with valid 
	separators. A separator is deemed as valid if it's outside any pair 
	of quotes.
*/

char	**ft_split_pipex(char *str, char *charset)
{
	char	**arr;
	int		word;

	word = count_word(str, charset);
	arr = (char **)malloc((word + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr = write_arr(arr, str, charset);
	arr[word] = NULL;
	return (arr);
}



static int	syntax_error(char *token, t_shell *ms)//error_occured need to revise only for parsing test
{
	char	c;

	c = *(token + 1);
	if (c == '\'' || c == '\"')
		ft_putstr_fd("unexpected EOF while looking for matching", 2);
	else
		ft_putstr_fd("syntax error near unexpected token", 2);
	ms->excode = 258;
	return (1);
}


int ifisredirect(char c)
{
    if ((c == '<' || c == '>'))
	{
		return (1);
	}
	return (0);
}


/* return 1 if char c is a spaces */
 int ifisspace(char c)
 {
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);				
	return (0);
}

int ifismeta (char c)
{
	if (c == ';' || c == '$' || c == '\'' || c == '\'')
		return (c);
	else
		return (0);
}

char *point_end(char *line)
{
    while (*line)
    {
        while (*line && *line != PIPE && *line != DOUBLEQUOTE && *line != SINGLEQUOTE)
          line++;
        if (*line == DOUBLEQUOTE || *line == SINGLEQUOTE)
        {
            line++;
            while(*line && *line != DOUBLEQUOTE && *line != SINGLEQUOTE)
            	line++;
            line++;
        }
        else
          return(line);
        
    }
    return(line);
}

char check_delimiter(char *line)
{
	char *single_quote;
	char *double_quote;

	single_quote = ft_strchr(line, '\'');
	double_quote = ft_strchr(line, '\"');
	if (!single_quote && !double_quote)
		return (0);
	else if ((single_quote && double_quote) && (single_quote > double_quote))
		return ('\"');
	else if (single_quote && double_quote)
		return ('\'');
	else if (double_quote)
		return ('\"');
	else 
		return ('\'');
}
	

int unclosed_quote(char *line)
{
	char delim;

	while(line)
	{
		delim = check_delimiter(line);//確認有沒有delimiter
		
		if (!delim)
			return (0);
		line = ft_strchr(line, delim);//把line指導有分隔號的地方
		if (!ft_strchr(line + 1, delim))
			return(delim);//果沒有成雙就返回表示錯誤
		line = ft_strchr(line + 1, delim) + 1;//將指針移到第二個分隔符號後，繼續檢查
	}
	return (0);
}

int invalid_redirect( char *line, char redirect)
{
	while(*line)
	{
		if (*line == '$' || (*line != redirect && !ifismeta(*line)))
			line++;
		else if (ifismeta(*line))// ' '' : 
		{
			line++;
			while (*line && *line != '\'' && *line != '\"')//echo "Hello World"
				line++;
			line++;//skip ' or "
		}
		else
		{
			line++;
			if (*line == redirect)
				line++;
			if (ifisspace(*line))
				line++;
			if (!*line || *line == '<' || *line == '>')
				return (1);//fail
		}
	}
	return (0);
}


int check_syntax(char *line, t_shell *ms)// mutiple pipe ... back slash, : export > ( syntax error near unexpected token `newline')
{
	char quote;
//檢查空輸入和管道符號
	//if (!line || !*line || *line == '|' || *(line + ft_strlen(line) - 1) == '|')
		//return (syntax_error("`|'", ms));//要改 error handling
//檢查未關閉的引號
	quote = unclosed_quote(line);
	if (quote == SINGLEQUOTE)
		return (syntax_error("`\''", ms));
	else if (quote == DOUBLEQUOTE)
		return (syntax_error("`\"'", ms));
//檢查無效的重定向

	if (invalid_redirect(line, '>'))
		return (syntax_error("`>'", ms));
	else if (invalid_redirect(line, '<'))
		return (syntax_error("`<'", ms));
	return (0);
}

void append_process_node(t_process_node **list, t_process_node *new)
{
	t_process_node *last_node;
	

	
	if (!*list)
		*list = new;
	else
	{
		
		
		last_node = *list;
		
		while(last_node->next)
			last_node = last_node->next;
		last_node->next = new;
	}
	
}

int count_cmd(t_process_node *list)
{
	int n;
	
	n = 0;
	while (list)
	{
		//dprintf(2,"list->node_line;%s\n", list->node_line );
		list = list->next;
		n++;
	}
	return (n);	
}

int empty_prompt(char *input)
{
	while (ifisspace(*input))
		input++;
	if (!*input)
		return (1);//true
	return (0);//false
}

int init_process_node(char *line, t_shell *ms)
{
    t_process_node *new;
    char *temp;

    if (!line || !*line || check_syntax(ms->line, ms) || empty_prompt(line))
        return (false);
    while (*line)
    {
        while (ifisspace(*line))
            line++;

        //make temp point to the end of the
        temp = point_end(line); 
        //calloc for new 
        new = ft_calloc(1, sizeof(t_process_node));
        // if (!new)
        //     error_handle();
		new->append = -1;
		new->heredoc = -1;
		new->expand = -1;
		new->doublequote = -1;
		new->sinquote = -1;
		new->redirectin = -1;
		new->redirectout= -1;
		new->command = NULL;
		new->node_line= NULL;// = input
		new->redirect_in= NULL;//< input
		new->redirect_out= NULL;//> output
		new->here_doc= NULL;//<<
		new->append_s= NULL;//>>
		new->cmd_path = NULL;
		new->node_line = ft_substr(line, 0, (temp - line));
		//dprintf(2, "new->node_line in init: %s\n",new->node_line );
        if (!new->node_line )
            free(new->node_line );

			
		append_process_node(&ms->list, new);// save every command in a node and append them to a list	
		
		//dprintf(2, "new->node_line after append: %s\n",new->node_line );
		
		check_syntax(new->node_line, ms);
	// malloc pids
		line = temp;
		if(*line)
			line++; //跳過pipe
    }
	ms->count = 0;
	ms->read_end = -1;
	ms->fd[0] = dup(STDIN_FILENO);//init as stdin
    ms->fd[1] = dup(STDOUT_FILENO);
	ms->execute = 0;
	ms->fork_n = count_cmd(ms->list);
	
	ms->pids = ft_calloc((ms->fork_n + 1), sizeof(int));//data->cmds, sizeof(int)
	if (ms->pids)
		return (-1);//error handle close_and_free
	ms->pids[0] = -1;
	return (0);
}

//char	*no_quote(char *cmd, t_process_node *mod) //for get_cmd_arr
char	*no_quote(char *cmd)//for test
{
	char	*result;
	int		new_len;
	int		i,j;
	
	j = 0;
	while (ifisspace(cmd[j]))
		j++;
	new_len = ft_strlen(cmd + j) - 1;//7
	result = malloc(sizeof(char) * new_len);
	if (result == NULL)
		ft_putstr_fd("malloc error", 2);// need change to print_error
	i = 0;
	
	while (i < new_len - 1)
	{
		result[i] = cmd[j+1];
		i++;
		j++;
	}
	result[i] = '\0';
	free(cmd);
	return (result);
}


char *check_if_quote(char *str)
{
	int k;

	k = 0;
	while (str[k])  //if quote
	{
		if (ft_strlen(str) > 1)
		{
			if ((str[k] == '\''
				&& str[ft_strlen(str) - 1]  == '\'') ||
				(str[k] == '"'
				&& str[ft_strlen(str) - 1] == '"'))
				str = no_quote(str);
		}
		k++;
	}
	return (str);
}


//檢查整句 input <>
char	*check_redirect( char *redirect, t_process_node *mod, t_shell *ms)
{
//redierect = > infile.txt
	char *end;
	static int i = 0;
	static int j = 0;
	int k;	

		
	if (*(redirect + 1) == '<')//<<heredoc
	{
		mod->heredoc = 1;
		redirect+= 2;
		mod->here_doc = redirect;
		//handdle_heredocs();
	}
	else if (*(redirect + 1) == '>')//>append
	{
		mod->append = 1;
		redirect = redirect + 2;
		mod->append_s = redirect;
		
		redir_append(redirect, ms);
	}
	else if (*redirect == '<')//in
	{
		k = 0;
		mod->redirectin = 1;
		redirect++;
		end = redirect;
		
		while (*end && !ifisredirect(*end))
			end++;
		// Ensure mod->redirect_out is allocated and has enough space
		if (mod->redirect_in == NULL) 
		{
			mod->redirect_in = malloc(sizeof(char *) * 100); // Define MAX_REDIRECTS appropriately
			if (mod->redirect_in == NULL) 
			{
				perror("redirect in malloc");
				return NULL; // Handle error or return as appropriate
			}
			ft_memset(mod->redirect_in, 0, sizeof(char *) * 100); // Initialize to NULL
		}
		mod->redirect_in[j] = ft_substr(redirect, 0, end - redirect);
		
		dprintf(2, "mod->redirect_in[j];%s\n",mod->redirect_in[j]);
		mod->redirect_in[j] = check_if_quote(mod->redirect_in[j]);
		if (ifisspace(mod->redirect_in[j][k]))
		 	k++;
		redir_in(mod->redirect_in[j] + k, ms);
		while (mod->redirect_in[j])
			j++;
		
		
				
	}	
	else if (*redirect == '>')//out
	{
		mod->redirectout = 1;
		
		redirect++;
		end = redirect;
		dprintf(2, "end in redirect: %s\n", end);
		while (*end && !ifisredirect(*end))
			end++;
		dprintf(2, "end in redirect 2: %s\n", end);
		// Ensure mod->redirect_out is allocated and has enough space
		if (mod->redirect_out == NULL) 
		{
			mod->redirect_out = malloc(sizeof(char *) * 100); // Define MAX_REDIRECTS appropriately
			if (mod->redirect_out == NULL) 
			{
				perror("redirect out malloc");
				return NULL; // Handle error or return as appropriate
			}
			ft_memset(mod->redirect_out, 0, sizeof(char *) * 100); // Initialize to NULL
		}
		mod->redirect_out[i] = ft_substr(redirect, 0, end - redirect);
		dprintf(2, "redirect in redirect: %s\n", redirect);
		dprintf(2, "end - redirect: %ld\n", end - redirect);
		dprintf(2, "1 mod->redirect_out[]:%s\n", mod->redirect_out[i]);
		mod->redirect_out[i] = check_if_quote(mod->redirect_out[i]);
		dprintf(2, "2 mod->redirect_out[i]:%s\n", mod->redirect_out[i]);
		redir_out(mod->redirect_out[i], ms);
		
		while (mod->redirect_out[i])
			i++;
		dprintf(2, "3 mod->redirect_out[i]: %s\n", mod->redirect_out[i]);
		
	}
	return (redirect);
}



// char **cmd_content_check(char **cmd)
// {
// 	int i;
// 	char *tmp;
	
// 	i = 0;
// 	while (cmd[i])
// 	{
// 		dprintf(2, "cmd[%d]-1:%s\n", i, cmd[i]);
// 		if (cmd[i][0] == '\'' || cmd[i][0] == '"' )
// 		{
// 			dprintf(2, "in loop\n");
// 			tmp = quote_remover(cmd[i]);
			
// 			if (!tmp)
// 				dprintf(2, "tmp is NULL");
// 			else 
// 				dprintf(2, "tmp:%s\n", tmp);
// 			if (!tmp)
// 			{
// 				free_single(cmd[i]);
// 				free (tmp);
				
// 				if (cmd[i + 1])
// 				{
// 					dprintf(2, "cmd[%d]:%s\n", i + 1, cmd[i+1]);
// 					free (cmd[i]);
// 					//cmd[i] = cmd[i + 1];
// 					dprintf(2, "cmd[%d]-2:%s\n", i, cmd[i]);
// 				}
// 				i--;
// 			}
// 			else
// 				cmd[i] = cmd[i];
			
// 		}
// 		i++;
// 	}
// 	return (cmd);	
// }


//char	**get_cmd_arr(char *command, t_process_node *mod)
char	**get_cmd_arr(char *command)
{
	char	**cmd_arr;
	//int		i;
	
	cmd_arr = ft_split_pipex(command, " ");
	if (cmd_arr == NULL)
		perror("maloc error");
	
	//cmd_arr = cmd_content_check(cmd_arr);//remove "" and ''
	//i = 0;
	//dont delete quote here
	// while (cmd_arr[i] != NULL)  
	// {
	// 	if (ft_strlen(cmd_arr[i]) > 1)
	// 	{
	// 		if ((cmd_arr[i][0] == '\''
	// 			&& cmd_arr[i][ft_strlen(cmd_arr[i]) - 1] == '\'') ||
	// 			(cmd_arr[i][0] == '"'
	// 			&& cmd_arr[i][ft_strlen(cmd_arr[i]) - 1] == '"'))
	// 			cmd_arr[i] = no_quote(cmd_arr[i]);
	// 	}
	// 	i++;
	// }
	return (cmd_arr);
}


void check_dollor(char **command, t_process_node *mod, t_shell *ms)
//void check_dollor(char **command)//for parse test
{
	int i, j;
	i = 0;
	
	while(command[i])//'hello $USER'
	{
		j = 0;
		while(command[i][j])
		{
			if (command[i][j] == '$')
			{
				//printf("check dollor command[i]: %s\n", command[i]);
				command[i] = expand_it_out(command[i], mod, ms);
				
			}	
			j++;
		}
		//dprintf(2, "a command[i]:%s\n", command[i]);
		command[i] = quote_remover(command[i]);
		//dprintf(2, "b command[i]:%s\n", command[i]);
		i++;
	}
}

char *go_check_redirect(char *input, t_process_node *mod, t_shell *ms)
{
	char *redirect;
	//char *end;
	//< infile.txt < infile << end
	
	redirect = input;
	while (*redirect)
	{
		if (!*redirect)
			break;
		while ( *redirect && !ifisredirect(*redirect))
			redirect++;
		//end = redirect;
		
		if (*redirect)
			redirect = check_redirect(redirect, mod, ms);//檢查redirect  input 0 redirect 19 
		else
			break;
		
		redirect++;
	}
	
	return (redirect);
}

void parse_mod(char *input, t_process_node *mod, t_shell *ms)
//void parse_mod(char *input, t_process_node *mod)// for parse test
{
	//echo "hello $USER" > infile.txt 
	//ls -la
	char *redirect;
	char *command;//input without redirection
	char *start;// check the first redirect for cmd
	
		while (ifisspace(*input) )
			input++;
		

		redirect  = get_fd(input, mod, ms);//redirection
		
		//go_check_redirect(input, mod, ms);
		
		
		
		start = input;
		while ( *start && !ifisredirect(*start))
				start++;
		
		//input  變成 echo "hello $USER"
		
		
		command = ft_substr( input, 0 , (start - input)); // may need free 
		
		dprintf(2, "command:%s\n", command);
		
		//get rid of ' '' save back to the string ; change mode
		mod->command = get_cmd_arr(command); //get (cmd[0]echo cmd[1]"hello $USER" or cmd[0]echo cmd[1]hello cmd[2]$USR)
		
		


		//command check
		int p = 0;
		while (mod->command[p])
		{
			dprintf(2, "mod->command[%d]:%s\n", p, mod->command[p]);
			p++;
		}
		

		
		if (is_builtin(mod->command[0]))
			mod->builtin = 1;
		
		/*
		echo
		hello $USER
		*/
		//check $  如果有＄ ---  mode 如果是雙引號 expand 把展開的內容存回 string
		check_dollor(mod->command, mod, ms);
}

//dive line by '|' and save them in linked list
void parse_process_node(t_process_node **list, t_shell *ms)
//void parse_process_node(t_process_node **list)//for parse test
{
	t_process_node *mod;//command node
	char *input;

	mod = *list;

	//dprintf(2, "ms->line: %s\n\n", ms->line);
	
	while (mod)
	{
		// if (mod->next)
		// 	input = mod->next->node_line;
		// else
		// 	input = mod->node_line;
		
		input = mod->node_line;
		//parse_mod(input, mod, ms);

		
		
		parse_mod(input, mod, ms);//for parse test
		
		
	
		ms->count++;
		mod = mod->next;
		// if (ms->list->next) //have to add this in order to also update the list to get the latest command
		// 	ms->list = ms->list->next;
	}
	
}

void execute_shell(t_shell *ms)
{
	
	parse_process_node(&ms->list, ms); //oritginal:parse_modules(&ms->mods, ms)
	//parse_process_node(&ms->list);//for parse test
	


	
	/* proper pipex
	if (!ms->list)
		exit(free_env(ms));
	else if (pipex(ms->list, ms) == -1)
		exit(ms->exitcode);
	*/
	pipex(ms->list, ms);//execute_children(ms); + wait_children(ms);
}

