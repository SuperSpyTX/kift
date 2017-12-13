/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 23:04:49 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/19 23:59:51 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;

	i = 0;
	if (len == 0)
		return (dst);
	if ((unsigned char*)src < (unsigned char*)dst)
	{
		while (--len > 0)
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
		((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
	}
	else
	{
		while (i < len)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i++;
		}
	}
	return (dst);
}
