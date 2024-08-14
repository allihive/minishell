/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:48:49 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/14 10:00:19 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_redirect_append(char *redirect, t_process_node *mod, t_shell *ms)
{
	char	*end;
	int		i;

	i = 0;
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
			perror("redirect out malloc"); //yunchia use adifferent function
			return (NULL);
		}
		ft_memset(mod->append_s, 0, sizeof(char *) * 100);
	}
	mod->append_s[i] = ft_substr(redirect, 0, end - redirect);
	mod->append_s[i] = check_if_quote(mod->append_s[i]);
	redir_append(mod->append_s[i], mod, ms, i);
	while (mod->append_s[i])
		i++;
	return (redirect);
}

char	*check_redirect_in(char *redirect, t_process_node *mod, t_shell *ms)
{
	char	*end;
	int		j;

	j = 0;
	if (ifisspace(*redirect))
		redirect++;
	end = redirect;
	while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
	if (mod->redirect_in == NULL)
	{
		mod->redirect_in = malloc(sizeof(char *) * 100);
		if (mod->redirect_in == NULL)
		{
			perror("redirect in malloc");//yunchia use adifferent function
			return (NULL);
		}
		ft_memset(mod->redirect_in, 0, sizeof(char *) * 100);
	}
	mod->redirect_in[j] = ft_substr(redirect, 0, end - redirect);
	mod->redirect_in[j] = check_if_quote(mod->redirect_in[j]);
	redir_in(mod->redirect_in[j], mod, ms, j);
	while (mod->redirect_in[j])
		j++;
	return (redirect);
}

char	*check_redirect_out(char *redirect, t_process_node *mod, t_shell *ms)
{
	char	*end;
	int		i;

	i = 0;
	while (ifisredirect(*redirect) || ifisspace(*redirect))
		redirect++;
	end = redirect;
	while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
	if (mod->redirect_out == NULL)
	{
		mod->redirect_out = malloc(sizeof(char *) * 100);
		if (mod->redirect_out == NULL)
		{
			perror("redirect out malloc"); //yunchia use adifferent function
			return (NULL);
		}
		ft_memset(mod->redirect_out, 0, sizeof(char *) * 100);
	}
	mod->redirect_out[i] = ft_substr(redirect, 0, end - redirect);
	mod->redirect_out[i] = check_if_quote(mod->redirect_out[i]);
	redir_out(mod->redirect_out[i], mod, ms, i);
	
	while (mod->redirect_out[i])
		i++;
	return (redirect);
}

char	*check_redirect(char *redirect, t_process_node *mod, t_shell *ms)
{
	if (*(redirect + 1) == '<')
	{
		handle_heredocs(redirect, mod, ms);
		redirect = redirect + 2;
	}
	else if (*(redirect + 1) == '>')
	{
		//mod->append = 1;
		redirect = redirect + 2;
		check_redirect_append(redirect, mod, ms);
	}
	else if (*redirect == '<')
	{
		//mod->redirectin = 1;
		redirect++;
		check_redirect_in(redirect, mod, ms);
	}	
	else if (*redirect == '>')
	{
		//mod->redirectout = 1;
		check_redirect_out(redirect, mod, ms);
	}
	return (redirect);
}

int	go_check_redirect(char *input, t_process_node *mod, t_shell *ms)
{
	char	*redirect;

	redirect = input;
	//dprintf(2, "in go check redirect:%s\n", redirect);
	while (*redirect)
	{
		if (!*redirect)
			break ;
		// while (*redirect && !ifisredirect(*redirect))
		// 	redirect++;



		while (*redirect && redirect_not_in_quote(*redirect, input, redirect - input, ms) == 0)
		{
			redirect++;
		
		}
	
		//dprintf(2, "2 in go check redirect:%s\n", redirect);
		if (*redirect)
			redirect = check_redirect(redirect, mod, ms);
		else
			break ;
		redirect++;
	}
	return (0);
}