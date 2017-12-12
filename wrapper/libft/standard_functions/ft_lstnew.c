/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 00:41:03 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 03:20:32 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstnew(const void *content, size_t content_size)
{
	t_list				*newlist;

	newlist = ft_memalloc(sizeof(t_list));
	if (!newlist)
		return (0);
	newlist->content = 0;
	newlist->content_size = 0;
	if (content)
	{
		newlist->content = ft_memalloc(content_size);
		if (!newlist->content)
		{
			ft_memdel((void*)&newlist);
			return (0);
		}
		ft_memcpy(newlist->content, content, content_size);
		newlist->content_size = content_size;
	}
	return (newlist);
}
