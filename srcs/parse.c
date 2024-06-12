/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:17:18 by yhsu              #+#    #+#             */
/*   Updated: 2024/06/12 13:26:04 by alli             ###   ########.fr       */
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
    if ((c == '<' || c == '>' ))
        return (1);
	return (0);
}


/* return 1 if char c is a spaces */
 int ifisspace(char c)
 {
	if (c == 32 || (c <= 9 && c >= 13))
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
        
//     }
//     return(line);
// }

char check_delimiter(line);
{
	char *single_quote;
	char *doublele_quote;

	single_quote = ft_strchr(line, '\'');
	doublele_quote = ft_strchr(line, '\"')
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
	

// int unclosed_quote(char *line)
// {
// 	char delim;

// 	while(line)
// 	{
// 		delim = check_delimiter(line);//確認有沒有delimiter
		
// 		if (!delim)
// 			return (0);
// 		line = ft_strchr(line, delim);//把line指導有分隔號的地方
// 		if (!ft_strchr(line + 1, delim))
// 			return(delim);//果沒有成雙就返回表示錯誤
// 		line = ft_strchr(line + 1, delim) + 1;//將指針移到第二個分隔符號後，繼續檢查
// 	}
// 	return (0);
// }

int invalid_redirect( char *line, char redirect)
{
	while(*line)
	{
		if (*line == '$' || (*line != redirect && *line != ifismeta(*line)))
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
			if (!*line || *line == '<' ||*line == '>')
				return (1);//fail
		}
	}
	return (0);
}



int check_syntax(char *line, t_shell *ms);// mutiple pipe ... back slash, : export > ( syntax error near unexpected token `newline')
{
	char quote;
//檢查空輸入和管道符號
	if (!line ||! *line || *line == '|' || *(line + ft_strlen(line) - 1) == '|')
		return (syntax_error());
//檢查未關閉的引號
	quote = unclosed_quote(line);
	if (quot == '\'')
		return (syntax_error());
	else if (quot == '\"')
		return (syntax_error());
//檢查無效的重定向
	if (invalid_redirect(line, '>'))
		return (syntax_error());
	else if (invalid_redirect(line, '<'))
		return (syntax_error());
	return (0);
}

void append_process_node(t_process_node *list, t_process_node *new)
{
	t_process_node *last_node;
	if (new == NULL)
		list = new;
	else
	{
		last_node= new;
		while(new->next)
			last_node = last_node->next;
		last_node->next = new;
	}
	new->next = NULL;
}

// int count_cmd(t_process_node *list)
// {
// 	int n;
	
// 	n = 0;
// 	while (list)
// 	{
		
		list = list->next;
		n++;
	}
	return (n);	
}

// int init_process_node(char *line, t_shell *ms)
// {
//     t_process_node *new;
//     char *temp;

    if (!line || !*line || check_syntax(ms->line, ms) || ifisspace(line))
        return (false);
    while (line)
    {

        while (ifisspace(line))
            line++;

        //make temp point to the end of the
        temp = point_end(line); 


        //calloc for new 
        new = ft_calloc(1, sizeof(t_process_node));
        // if (!new)
        //     error_handle();
        new->fd_in = -1;
        new->fd_out = -1;
		new->command = NULL;
        if (new->node_line)
            new->node_line = ft_substr(line, 0, (temp - line));
        if (!new->node_line )
            free(new->node_line );
		append_process_node(ms->list, new);// save every command in a node and append them to a list
		check_syntax(new->node_line, ms);
	// malloc pids
		line = temp;
		if(*line)
			line++; //跳過pipe
    }
	ms->fork_n = count_cmd(ms->list);
	ms->pids = ft_calloc(1,ms->fork_n * sizeof(pid_t));
	return (0);
}

void parse_mod(char *input, t_process_node mod, t_shell ms)
{
	while( *input)//  echo "hello $USER" > infile.txt
	{
			//檢查redirevt

			//
	}
}


void parse_process_node(t_process_node *list, t_shell *ms)
{
	t_process_node *mod;//command node
	char *input;

	while (mod)
	{
		input = mod->node_line;
		parse_mod(input, mod, ms);

		//if (mod->command != NULL)
			//parse_expands(mod, ms);??

		mod = mod->next;
	}
}

static void execute_shell(t_shell *ms)
{
	parse_process_node(&ms->list, ms); //oritginal:parse_modules(&ms->mods, ms)
	//execute_children(ms);
	//wait_children(ms);
}
