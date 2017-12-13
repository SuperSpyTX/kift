/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 20:08:04 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 16:04:32 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
** I really just wanted this function to work.
** Nobody will want to use this function anyways.........
** If any tests fail, try using n = size - dlen;
*/

size_t				ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dlen;
	size_t			n;
	size_t			slen;
	size_t			i;

	n = size;
	slen = 0;
	dlen = 0;
	while (n-- != 0 && dst[dlen] != '\0')
		dlen++;
	n += 1;
	if (n == 0)
		return (dlen + ft_strlen(src));
	i = 0;
	while (src[slen] != '\0')
	{
		if (n != 1)
		{
			dst[dlen + i++] = src[slen];
			n--;
		}
		slen++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
