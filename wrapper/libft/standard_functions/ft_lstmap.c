/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 00:43:07 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 03:29:18 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list				*nlist;
	t_list				*pls;

	if (!lst)
		return (0);
	nlist = f(lst);
	pls = nlist;
	while (lst->next)
	{
		lst = lst->next;
		if (!(nlist->next = f(lst)))
		{
			free(nlist->next);
			return (0);
		}
		nlist = nlist->next;
	}
	return (pls);
}
