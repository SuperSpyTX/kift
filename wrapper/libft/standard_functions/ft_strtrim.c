/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:26:13 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/20 17:38:55 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int			is_special_whitespace(const char c)
{
	if (c != '\0' && (c == ' ' || c == '\n' || c == '\t'))
		return (1);
	return (0);
}

char				*ft_strtrim(char const *s)
{
	size_t				len;
	size_t				begin;
	int					end;

	if (!s)
		return (0);
	len = ft_strlen(s);
	end = len - 1;
	begin = -1;
	while (is_special_whitespace(s[++begin]) && begin < len)
		;
	while (is_special_whitespace(s[end--]) && end > -1)
		;
	if (end == -1 || begin >= len)
		return (ft_strnew(1));
	else
	{
		len = ++end - begin + 1;
		return (ft_strsub(s, begin, len));
	}
}
