/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:40:24 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 13:17:41 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//dprintf(2,"str[%d]:%c\n", i,str[i]);
		while (is_sep(str, i, charset) )
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
	//dprintf(2,"dest:%s\n", dest);
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
			{
				// while (--word)
				// 	free(arr[word]);
				return (NULL);
			}
			arr[word] = write_word(arr[word], str + i, charset);

			//dprintf(2,"arr[%d]:%s\n", word,  arr[word]);

			
			i += len;
			len = 0;
			word++;
		}
	}
	return (arr);
}

static char	**ft_split_pipex(char *str, char *charset)
{
	char	**arr;
	int		word;

	word = count_word(str, charset);
	
	arr = (char **)malloc((word + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr = write_arr(arr, str, charset);
	
	arr[word] = NULL;
	
	// int i = 0;
	// while (arr[i])
	// {
	// 	dprintf(2, "arr[i]: %s\n", arr[i]);
	// 	i++;
	// }



	
	return (arr);
}

//char	**get_cmd_arr(char *command, t_process_node *mod)
char	**get_cmd_arr(char *command, t_shell *ms)
{
	char	**cmd_arr;

	
	cmd_arr = ft_split_pipex(command, " ");
	if (cmd_arr == NULL)
	{
		perror("maloc error");
		close_and_free(ms);
	}
	
	return (cmd_arr);
}
