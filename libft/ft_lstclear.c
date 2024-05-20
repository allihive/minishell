/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:40:43 by alli              #+#    #+#             */
/*   Updated: 2023/11/10 16:33:49 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*all;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		all = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = all;
	}
	free(*lst);
}
