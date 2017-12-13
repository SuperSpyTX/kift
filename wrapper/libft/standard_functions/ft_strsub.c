/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:07:17 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/20 17:18:29 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*newstr;
	size_t			max_size;
	size_t			i;
	size_t			ni;

	if (!s)
		return (0);
	i = (size_t)start - 1;
	ni = 0;
	max_size = i + 1 + len;
	newstr = ft_strnew(len);
	if (!newstr)
		return (0);
	while (++i < max_size)
		newstr[ni++] = s[i];
	newstr[ni] = 0;
	return (newstr);
}
