/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:48:49 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/31 12:20:52 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_redirect_in(char *redirect, t_process_node *mod, t_shell *ms)
{
	char *end;
	int j;
	
	j = 0;
	if (ifisspace(*redirect))//  remove space the the beginning
		redirect++;
	end = redirect;
	while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
	if (mod->redirect_in == NULL) 
	{
		mod->redirect_in = malloc(sizeof(char *) * 100); // Define MAX_REDIRECTS appropriately
		if (mod->redirect_in == NULL) 
		{
			perror("redirect in malloc");
			return NULL; // Handle error or return as appropriate
		}
		ft_memset(mod->redirect_in, 0, sizeof(char *) * 100); // Initialize to NULL
	}
	mod->redirect_in[j] = ft_substr(redirect, 0, end - redirect);
	mod->redirect_in[j] = check_if_quote(mod->redirect_in[j]);
	redir_in(mod->redirect_in[j], ms, j);
	while (mod->redirect_in[j])
		j++;
	return (redirect);
}

char *check_redirect_out(char *redirect, t_process_node *mod, t_shell *ms)
{
	char *end;
	static int i = 0;
	
	while (ifisredirect(*redirect) || ifisspace(*redirect))
		redirect++;
	end = redirect;
	while (*end && !ifisredirect(*end) && *end != ' ')
		end++;
	if (mod->redirect_out == NULL) 
	{
		mod->redirect_out = malloc(sizeof(char *) * 100); // Define MAX_REDIRECTS appropriately
		if (mod->redirect_out == NULL) 
		{
			perror("redirect out malloc");
			return NULL; // Handle error or return as appropriate
		}
		ft_memset(mod->redirect_out, 0, sizeof(char *) * 100); // Initialize to NULL
	}
	mod->redirect_out[i] = ft_substr(redirect, 0, end - redirect);
	mod->redirect_out[i] = check_if_quote(mod->redirect_out[i]);
	redir_out(mod->redirect_out[i], ms, i);
	while (mod->redirect_out[i])
		i++;
	return (redirect);
}

//檢查整句 input <>
char	*check_redirect(char *redirect, t_process_node *mod, t_shell *ms)
{
	if (*(redirect + 1) == '<')//<<heredoc
	{
		handle_heredocs(redirect, mod, ms);
		redirect = redirect + 2;
	}
	else if (*(redirect + 1) == '>')//>>append
	{
		mod->append = 1;
		redirect = redirect + 2;
		mod->append_s = redirect;
		redir_append(redirect, ms);
	}
	else if (*redirect == '<')//in
	{
		mod->redirectin = 1;
		redirect++;
		check_redirect_in(redirect, mod, ms);		
	}	
	else if (*redirect == '>')//out
	{
		mod->redirectout = 1;
		check_redirect_out(redirect, mod, ms);
	}
	return (redirect);
}


int go_check_redirect(char *input, t_process_node *mod, t_shell *ms)
{
	char *redirect;
	
	redirect = input;
	while (*redirect)
	{
		if (!*redirect)
			break;
		while ( *redirect && !ifisredirect(*redirect))
			redirect++;
		if (*redirect)
			redirect = check_redirect(redirect, mod, ms);//檢查redirect  input 0 redirect 19 
		else
			break;
		redirect++;
	}
	return (0);
}