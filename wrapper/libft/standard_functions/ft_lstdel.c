/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 00:42:11 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 03:16:00 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list				*twanna;
	t_list				*temp;

	twanna = (*alst)->next;
	while (twanna)
	{
		temp = twanna->next;
		ft_lstdelone(&twanna, del);
		twanna = temp;
	}
	ft_lstdelone(alst, del);
}
