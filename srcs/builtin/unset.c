/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:18:43 by alli              #+#    #+#             */
/*   Updated: 2024/06/24 10:12:49 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *name_exists(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	// printf("name: %s\n", name);
	while(name[i] && name[i] != '=')
		i++;
	key = ft_substr(name, 0, i);
	if (!key)
		return (NULL); //should be error_handle
	// printf("key: %s\n", key);
	len = ft_strlen(key);
	i = 0;
	while (i < ms->envp_size && ms->envp[i])
	{
		
		if ((ft_strncmp(key, ms->envp[i], len) == 0) 
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
				return (ms->envp[i] + len);
		i++;
	}
	return (NULL);
}

void    envp_delete(t_shell *ms, char *name)
{
    char    **new;
    int     i;
    int     j;
    int     len;

    i = 0;
    j = 0;
    len = ft_strlen(name);
    new = ft_calloc((ms->envp_size - 1), sizeof(char *));
    if (!new)
        return ;//error handle
    while(i < ms->envp_size && ms->envp[i]) //i < ms->envp_size && 
    {
        if (!ft_strncmp(ms->envp[j], name, len) && 
            ((ms->envp[j][len] == '=') || (ms->envp[j][len] == '\0')))//what happened to ft_strncmp?
        {
            printf("entered ft_strncmp");
            j++;
        }
        else
        {
			printf("entered else");
            new[i++] = ft_strdup(ms->envp[j++]);
        }

    }
    ms->envp_size -= 1;
    ft_free_strs(ms->envp, 0, 0);
    ms->envp = new;
}

void	unset(t_shell *ms, char **cmd)
{
	// char    **tmp;
    int     i;
    // int     j;
    
    i = 0;
    // j = 0;
	printf("unset\n");
    while (cmd[i])
    {
		printf("name_exists %s\n", name_exists(ms, cmd[1]));
        if (name_exists(ms, cmd[1])) //tmp should be a=1
        {
            printf("unset cmd[1] %s\n", cmd[1]);
            envp_delete(ms, cmd[1]);
            return ;
        }
        i++;
    }
}
