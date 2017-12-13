/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 01:18:58 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 14:02:08 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t				c;

	c = 0;
	while (src[c] != 0 && c < len)
	{
		dest[c] = src[c];
		c++;
	}
	while (c < len)
	{
		dest[c] = '\0';
		c++;
	}
	return (dest);
}
