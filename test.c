
# include <stdio.h>
# include <termios.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <string.h> 
typedef struct s_process_node
{
	char **command; 
	char *node_line;// = input
	char *redirect_in;//< input
	char *redirect_out;//> output
	char *heredoc;//<<
	char *append;//>>
	int fd_in;
	int fd_out;
	int pipe;
	int sinquote;
	int doublequote;
	

	int		meta;
	int		process_mode;
	
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

int ifisredirect(char c)
{
    if ((c == '<' || c == '>' ))
        return (1);
	return (0);
}
 int ifisspace(char c)
 {
	if (c == '&' || (c <= 9 && c >= 13))
		return (1);				
	return (0);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		len;

	len = strlen(src);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == '\0')
		return (0);
	strlcpy(dest, src, len + 1);
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;
	size_t	newlen;

	j = 0;
	newlen = 0;
	if (start >= strlen(s))
		return (ft_strdup(""));
	if (start + len > strlen(s))
		newlen = strlen(s) - start;
	else
		newlen = len;
	str = (char *)malloc(sizeof(char) * (newlen + 1));
	if (!str || !s)
		return (NULL);
	while (start < strlen(s) && j < len)
	{
		str[j] = s[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}


void check_redirect(char *input, char *redirect)
{
//redierect = > infile.txt
		if (*(redirect + 1) == '>')//>
		{
			//mod->append = 1;
			redirect += 2;
			//mod->append = redirect;
		}	
		else if (*(redirect + 1) == '<')//<
		{
			//mod->heredoc = 1;
			redirect += 2;
			//char *heredoc = redirect;
		}
		else if (*redirect == '>')
		{
			//mod->redirect_in = 1;
			redirect ++;
			//mod->redirect_in= redirect;
		}	
		else if (*redirect == '<')
		{
			//mod->redirect_out = 1;
			redirect ++;
			//mod->redirect_in= redirect;
		}
}

//void parse_mod(char *input, t_process_node *mod, t_shell *ms)
char * parse_mod(char *input)
{
	//echo "hello $USER" > infile.txt
	char *redirect;
	
			while(ifisspace(*input))
			    input++;
			//if (!*input)
				//break;
			redirect = input;
			while (!ifisredirect(*redirect))
				input++;
			check_redirect(input, redirect);//檢查redirect  input 0 redirect 19 
			//input  變成 echo "hello $USER"
			input = ft_substr( input,0 , (redirect - input));
    return (input);
}
char	*no_quote(char *cmd)
{
	char	*result;
	int		new_len;
	int		i;

	new_len = strlen(cmd) - 1;
	result = malloc(sizeof(char) * new_len);
	//if (result == NULL)
	//	print_error("maloc error", pipex, EXIT_FAILURE);
	i = 0;
	while (i < new_len - 1)
	{
		result[i] = cmd[i + 1];
		i++;
	}
	result[i] = '\0';
	free(cmd);
	return (result);
}


char	**get_cmd_arr(char *command)
{
	char	**cmd_arr;
	int		i;

	cmd_arr = ft_split_pipex(command, " ");
	//if (cmd_arr == NULL)
		//print_error("maloc error", mod, EXIT_FAILURE);
	i = 0;
	while (cmd_arr[i] != NULL)
	{
		if (strlen(cmd_arr[i]) > 1)
		{
			if ((cmd_arr[i][0] == '\''
				&& cmd_arr[i][strlen(cmd_arr[i]) - 1] == '\'') ||
				(cmd_arr[i][0] == '"'
				&& cmd_arr[i][strlen(cmd_arr[i]) - 1] == '"'))
				cmd_arr[i] = no_quote(cmd_arr[i]);
		}
		i++;
	}
	return (cmd_arr);
}

int main ()
{
	char *s = "echo "hello '$USER'"";
	printf("s:%s\n", s);
	char	**cmd_arr = get_cmd_arr(s);
	int i = 0;
	while (cmd_arr[i])
	{
		printf("cmd_arr:%s\n", cmd_arr[i]);
		i++;
	}
   
    
}
