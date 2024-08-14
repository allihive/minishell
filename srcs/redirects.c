/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:48:49 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 12:36:26 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_redirect_append(char *redirect, t_process_node *mod,
	t_shell *ms, int i)
{
	char	*end;

	while (ifisredirect(*redirect) || ifisspace(*redirect))
		redirect++;
	end = redirect;
	while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
	if (mod->append_s == NULL)
	{
		mod->append_s = malloc(sizeof(char *) * 100);
		if (mod->append_s == NULL)
		{
			ft_putstr_fd("redirect out malloc", 2);
		}
		ft_memset(mod->append_s, 0, sizeof(char *) * 100);
	}
	mod->append_s[i] = ft_substr(redirect, 0, end - redirect);
	mod->append_s[i] = check_if_quote(mod->append_s[i]);
	if (redir_append(mod->append_s[i], mod, ms, i) == -1)
		return (NULL);
	return (redirect);
}

char	*check_redirect_in(char *redirect, t_process_node *mod,
	t_shell *ms, int j)
{
	char	*end;

	if (ifisspace(*redirect))
		redirect++;
	end = redirect;
	while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
	if (mod->redirect_in == NULL)
	{
		mod->redirect_in = ft_calloc(1, sizeof(char *) * 100);
		if (mod->redirect_in == NULL)
		{
			ft_putstr_fd("redirect in malloc", 2);
			return (NULL);
		}
	}
	mod->redirect_in[j] = ft_substr(redirect, 0, end - redirect);
	mod->redirect_in[j] = check_if_quote(mod->redirect_in[j]);
	if (redir_in(mod->redirect_in[j], mod, ms, j) == -1)
		return (NULL);
	while (mod->redirect_in[j])
		j++;
	return (redirect);
}

char	*check_redirect_out(char *redirect, t_process_node *mod,
	t_shell *ms, int i)
{
	char	*end;

	while (ifisredirect(*redirect) || ifisspace(*redirect))
		redirect++;
	end = redirect;
	while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
	if (mod->redirect_out == NULL)
	{
		mod->redirect_out = ft_calloc(1, sizeof(char *) * 100);
		if (mod->redirect_out == NULL)
		{
			ft_putstr_fd("redirect out malloc", 2);
			return (NULL);
		}
	}
	mod->redirect_out[i] = ft_substr(redirect, 0, end - redirect);
	mod->redirect_out[i] = check_if_quote(mod->redirect_out[i]);
	if (redir_out(mod->redirect_out[i], mod, ms, i) == -1)
		return (NULL);
	return (redirect);
}

char	*check_redirect(char *redirect, t_process_node *mod, t_shell *ms, int i)
{
	if (*(redirect + 1) == '<')
	{
		handle_heredocs(redirect, mod, ms);
		redirect = redirect + 2;
	}
	else if (*(redirect + 1) == '>')
	{
		mod->append = 1;
		redirect = redirect + 2;
		if (!check_redirect_append(redirect, mod, ms, i))
			return (NULL);
	}
	else if (*redirect == '<')
	{
		redirect++;
		if (!check_redirect_in(redirect, mod, ms, i))
			return (NULL);
	}	
	else if (*redirect == '>')
	{
		if (!check_redirect_out(redirect, mod, ms, i))
			return (NULL);
	}
	return (redirect);
}

int	go_check_redirect(char *input, t_process_node *mod, t_shell *ms)
{
	char	*redirect;
	int		i;

	i = 0;
	redirect = input;
	while (*redirect)
	{
		if (!*redirect)
			break ;
		while (*redirect && redirect_not_in_quote(*redirect,
				input, redirect - input, ms) == 0)
			redirect++;
		if (*redirect)
		{
			redirect = check_redirect(redirect, mod, ms, i);
			if (!redirect)
				return (-1);
		}
		else
			break ;
		redirect++;
		i++;
	}
	return (0);
}
