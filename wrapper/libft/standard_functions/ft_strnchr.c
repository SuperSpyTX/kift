/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 19:41:06 by jkrause           #+#    #+#             */
/*   Updated: 2017/07/16 17:49:30 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnchr(const char *s, int c, size_t size)
{
	ssize_t					len;

	len = -1;
	while (++len < (ssize_t)size && (unsigned char)*s != (unsigned char)c && *s)
		(void)*s++;
	if (len >= (ssize_t)size || (!*s && c != 0))
		return (0);
	return ((char*)s);
}
