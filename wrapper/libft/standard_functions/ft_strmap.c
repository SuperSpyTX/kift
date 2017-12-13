/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:06:02 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/20 17:21:54 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmap(char const *s, char (*f)(char))
{
	size_t			i;
	size_t			siz;
	char			*newstr;

	if (!s || !f)
		return (0);
	siz = ft_strlen(s);
	newstr = ft_strnew(siz);
	if (!newstr)
		return (0);
	i = -1;
	while (++i < siz)
		newstr[i] = f(s[i]);
	return (newstr);
}
