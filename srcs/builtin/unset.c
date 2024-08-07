/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:18:43 by alli              #+#    #+#             */
/*   Updated: 2024/08/07 09:49:32 by alli             ###   ########.fr       */
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
	ms->envp_size -= 1;
    len = ft_strlen(name);
    new = ft_calloc((ms->envp_size + 1), sizeof(char *));
    if (!new)
        return ;//error handle
    while(j < ms->envp_size && ms->envp[i]) //i < ms->envp_size && 
    {
        if (!ft_strncmp(ms->envp[j], name, len) && 
            ((ms->envp[j][len] == '=') || (ms->envp[j][len] == '\0')))
            j++;
        else
            new[i++] = ms->envp[j++]; //new[i++] = ft_strdup(ms->envp[j++]);
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
            // return ;
        }
        i++;
    }
	ms->excode = 0;
}
