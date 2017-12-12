/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:00:57 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 03:15:20 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char			*m1;
	unsigned char			*m2;

	if (n == 0)
		return (0);
	m1 = (unsigned char*)s1;
	m2 = (unsigned char*)s2;
	while (n > 1 && *m1 == *m2)
	{
		(void)*m1++;
		(void)*m2++;
		n -= 1;
	}
	return ((unsigned char)(*m1) - (unsigned char)(*m2));
}
