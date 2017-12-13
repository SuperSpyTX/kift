/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 00:42:49 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 03:15:38 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list				*temp;

	temp = lst;
	while (temp)
	{
		f(temp);
		temp = temp->next;
	}
}
