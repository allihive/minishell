/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:18:43 by alli              #+#    #+#             */
/*   Updated: 2024/06/19 16:15:26 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *name_exists(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	while(name[i] && (name[i] != '\0' || name[i] != '='))
		i++;
	key = ft_substr(name, 0, i);
	if (!key)
		return (NULL); //should be error_handle
	len = ft_strlen(key);
	i = 0;
	while (i < ms->envp_size)
	{
        if (!ms->envp[i])
            printf("NULL\n");
        printf("ms->envp[j]: %s\n", ms->envp[i]);
        printf("name: %s\n", name);
		if ((!ft_strncmp(key, ms->envp[i], len)) && 
            (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
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
    // while(i < ms->envp_size)
    // {
    //     printf("ms->envp[%d]: %s", i, ms->envp[i]);
    //     i++;
    // }
    // i = 0;
    while(ms->envp[i] != NULL)
    {
        if (!ms->envp[j])
            printf("AAAAAAAAAAAHHHHHH NULL\n"); //so only segfaulting on the last 
        if (!ft_strncmp(ms->envp[j], name, len) && 
            ((ms->envp[j][len] == '=') || (ms->envp[j][len] == '\0')))//what happened to ft_strncmp?
            j++;
        else
            new[i++] = ft_strdup(ms->envp[j++]);
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
    while (cmd[i])
    {
        if (name_exists(ms, cmd[1])) //tmp should be a=1
        {
            envp_delete(ms, cmd[1]);
            return ;
        }
        i++;
    }
}
