/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:18:43 by alli              #+#    #+#             */
/*   Updated: 2024/08/07 14:33:32 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *name_exists_unset(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	printf("name: %s\n", name);
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
			{
				// printf("key found %s\n", key);
				free(key);
				return (ms->envp[i] + len);
			}
		i++;
	}
	free(key);
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
	printf("before ms->envp_size %d\n", ms->envp_size);
	ms->envp_size -= 1;
	printf("after ms->envp_size %d\n", ms->envp_size);
    len = ft_strlen(name);
    new = ft_calloc((ms->envp_size), sizeof(char *));
    if (!new)
        return ;
    while(j < ms->envp_size && ms->envp[j]) //j < ms->envp_size &&  
    {
        if (!ft_strncmp(ms->envp[j], name, len) && 
            ((ms->envp[j][len] == '=') || (ms->envp[j][len] == '\0')))
		{
		
            j++;
		}
        else
		{
            new[i] = ms->envp[j]; 
			i++;
			j++;
			printf("new[i] = %s\n", new[i]);
			printf("ms->envp[%d] %s\n", j, ms->envp[i]);
		}
    }
	new[i] = "\0";
    free(ms->envp);
    ms->envp = new;
}

void	unset(t_shell *ms, char **cmd)
{
	// char    **tmp;
    int     i;
    // int     j;
    
    i = 0;
    // j = 0;
	// printf("unset\n");
    while (cmd[i])
    {
        if (name_exists_unset(ms, cmd[i])) //tmp should be a=1
        {
            envp_delete(ms, cmd[i]);
        }
        i++;
    }
	ms->excode = 0;
}
