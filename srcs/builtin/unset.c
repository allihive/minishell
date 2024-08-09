/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:18:43 by alli              #+#    #+#             */
/*   Updated: 2024/08/09 10:54:37 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*name_exists_unset(t_shell *ms, char *name)
{
	int		len;
	int		i;
	char	*key;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	key = ft_substr(name, 0, i);
	if (!key)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (i < ms->envp_size && ms->envp[i])
	{
		if ((ft_strncmp(key, ms->envp[i], len) == 0)
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
		{
			free(key);
			return (ms->envp[i] + len);
		}
		i++;
	}
	free(key);
	return (NULL);
}

void	copy_new_array(char **new, char **old_envp, int i, int j)
{
	new[i] = old_envp[j];
	return ;
}

void	envp_delete(t_shell *ms, char *name)
{
	char	**new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	ms->envp_size -= 1;
	len = ft_strlen(name);
	new = ft_calloc((ms->envp_size + 1), sizeof(char *));
	if (!new)
		return ;
	while (j < ms->envp_size + 1 && ms->envp[i])
	{
		if (!ft_strncmp(ms->envp[j], name, len)
			&& ((ms->envp[j][len] == '=') || (ms->envp[j][len] == '\0')))
		{
			free(ms->envp[j]);
			j++;
		}
		else
			copy_new_array(new, ms->envp, i++, j++);
	}
	free(ms->envp);
	ms->envp = new;
}

void	unset(t_shell *ms, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (name_exists_unset(ms, cmd[i]))
		{
			envp_delete(ms, cmd[i]);
		}
		i++;
	}
	ms->excode = 0;
}
