/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:55:16 by yhsu              #+#    #+#             */
/*   Updated: 2024/08/13 16:48:22 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int check_redir_quote(char *str, int *quote_status)
// {
//     int l;
//     int quote;

// 	l = 0;
// 	quote = -1;
//     while (str[l])
//     {
//         if (str[l] == DOUBLEQUOTE && quote == -1)
//             quote = DOUBLEQUOTE;
//         else if (str[l] == DOUBLEQUOTE && quote == DOUBLEQUOTE)
//             quote = -1;
//         else if (str[l] == SINGLEQUOTE && quote == -1)
//             quote = SINGLEQUOTE;
//         else if (str[l] == SINGLEQUOTE && quote == SINGLEQUOTE)
//             quote = -1;
//         l++;
//     }
//     *quote_status = quote;
//     return (quote != -1);
// }
// {
//     int quote_status;
//     char *tmp;

//     if (c == '<' || c == '>')
//     {
//         tmp = ft_substr(input, 0, k);
        
//         if (check_redir_quote(tmp, &quote_status))
//         {
//             free(tmp);
//             return 0;
//         }
//         free(tmp);
//         if (quote_status != -1)
//         {
//             ms->execute = -1;
//             return 1;
//         }
//         else
//             return 0;
//     }
//     else
//         return 0;
// }