/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:48:49 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/26 15:09:43 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//檢查整句 input <>
char	*check_redirect(char *redirect, t_process_node *mod, t_shell *ms)
{
//redierect = > infile.txt
	char *end;
	
	static int j = 0;
	int k;	

		
	if (*(redirect + 1) == '<')//<<heredoc
	{
		// mod->heredoc = 1;
		// redirect+= 2;
		// mod->here_doc = redirect;
		// dprintf(2, "mod->here_doc: %s\n", mod->here_doc) ;
		
		
		handle_heredocs(redirect, mod, ms);
		// while (!ifisredirect(*(redirect + 2)))
		// 	redirect++;
		redirect = redirect + 2;
		
		//handle_heredocs(redirect, mod);
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
		k = 0;
		mod->redirectin = 1;
		redirect++;
		end = redirect;
		
		while (*end && !ifisredirect(*end))
			end++;
		// Ensure mod->redirect_out is allocated and has enough space
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
		
		//may need to free redirect
		
		
		//dprintf(2, "mod->redirect_in[j];%s\n",mod->redirect_in[j]);
		mod->redirect_in[j] = check_if_quote(mod->redirect_in[j]);
		if (ifisspace(mod->redirect_in[j][k]))
		 	k++;
		redir_in(mod->redirect_in[j] + k, ms);

		dprintf(2, "mod->redirect_in[j];%s\n",mod->redirect_in[j]);
		while (mod->redirect_in[j])
			j++;
			
	}	
	else if (*redirect == '>')//out
	{
		//dprintf(2, "in redirect out\n");
		static int i = 0;
		mod->redirectout = 1;
		
		redirect++;
		end = redirect;
		dprintf(2, "end in redirect: %s\n", end);
		while (*end && !ifisredirect(*end))
			end++;
		//dprintf(2, "end in redirect 2: %s\n", end);
		// Ensure mod->redirect_out is allocated and has enough space
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
		//dprintf(2, "in redirect out1\n");
		mod->redirect_out[i] = ft_substr(redirect, 0, end - redirect);
		mod->redirect_out[i] = check_if_quote(mod->redirect_out[i]);
		
		redir_out(mod->redirect_out[i], ms);
	
		while (mod->redirect_out[i])
			i++;
		//redirect = redirect + ft_strlen(mod->redirect_out[i - 1]); 
	}
	
	return (redirect);
}


int go_check_redirect(char *input, t_process_node *mod, t_shell *ms)
{
	char *redirect;
	//char *end;
	//< infile.txt < infile << end
	
	redirect = input;
	while (*redirect)
	{
		if (!*redirect)
			break;
		while ( *redirect && !ifisredirect(*redirect))
			redirect++;
		//end = redirect;
		
		dprintf(2, "reidrect in check_redirect: %s\n", redirect);
		
		if (*redirect)
			redirect = check_redirect(redirect, mod, ms);//檢查redirect  input 0 redirect 19 
		else
			break;
		
		redirect++;
	}
	
	//return (redirect);
	return (0);
}