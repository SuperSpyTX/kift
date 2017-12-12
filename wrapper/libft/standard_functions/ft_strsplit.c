/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:47:31 by jkrause           #+#    #+#             */
/*   Updated: 2017/08/27 08:07:31 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void			dynamic_resize(size_t **ptr, size_t *current_size)
{
	size_t *newptr;

	newptr = ft_memalloc(*current_size + sizeof(size_t));
	ft_memcpy(newptr, *ptr, *current_size);
	if (*current_size != 0)
		ft_memdel((void**)ptr);
	*ptr = newptr;
	*current_size += sizeof(size_t);
}

static void			dyn_insert(size_t **ptr, size_t *size, size_t i1, size_t i2)
{
	dynamic_resize(ptr, size);
	(*ptr)[(*size / sizeof(size_t)) - 1] = i1;
	dynamic_resize(ptr, size);
	(*ptr)[(*size / sizeof(size_t)) - 1] = i2;
}

static char			**apply_substr(char const *s, size_t *m,
						size_t msize, char c)
{
	char				**buffer;
	char				*newstr;
	size_t				i;
	size_t				b;

	msize /= sizeof(size_t);
	buffer = (char**)ft_memalloc(sizeof(char*) * (msize + 1));
	if (!buffer)
		return (0);
	i = 0;
	b = 0;
	while (i < msize)
	{
		(void)c;
		newstr = ft_strsub(s, m[i], m[i + 1]);
		if (i + 1 == (msize - 1) && ((unsigned char*)s)[m[i] + m[i + 1]] != c)
			newstr = ft_strsub(s, m[i], m[i + 1] + 1);
		buffer[b++] = newstr;
		i += 2;
	}
	buffer[b] = 0;
	return (buffer);
}

static void			move_ptr(char const *s, char c, size_t *i, int flag)
{
	if (flag)
		while (s[*i] != c && s[*i + 1] != '\0')
			*i += 1;
	else
		while (s[*i] == c || s[*i + 1] == '\0')
		{
			*i += 1;
		}
}

char				**ft_strsplit(char const *s, char c)
{
	size_t				*matches;
	size_t				cngowillnever;
	size_t				a;
	size_t				i;

	matches = ft_memalloc(1);
	if (!s || !matches)
		return (0);
	cngowillnever = 1;
	i = 0;
	a = 0;
	while (s[i] != '\0')
		if (s[i] != c && s[i + 1] != '\0')
		{
			a = i;
			move_ptr(s, c, &i, 1);
		}
		else
		{
			if (i != a)
				dyn_insert(&matches, &cngowillnever, a, (i - a));
			move_ptr(s, c, &i, 0);
		}
	return (apply_substr(s, matches, cngowillnever, c));
}
