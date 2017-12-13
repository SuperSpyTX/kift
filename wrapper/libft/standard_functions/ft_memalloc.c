/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 16:53:27 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/22 15:30:02 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memalloc(size_t size)
{
	void		*alloc;

	alloc = malloc(size);
	if (alloc)
		ft_memset(alloc, 0, size);
	return (alloc ? alloc : 0);
}
