/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:24:32 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/22 15:13:39 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Thanks to @mfriedri
*/

t_no					*ft_no(void *anything)
{
	t_no				*result;

	(void)anything;
	result = (t_no*)ft_memalloc(sizeof(t_no*));
	result->zero = 0;
	result->value = "no";
	return (result);
}
