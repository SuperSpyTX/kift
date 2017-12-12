/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 01:54:43 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/15 01:36:33 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int							malloc_or_use(int fd, t_descriptor *desc, int reset)
{
	int								res;

	if (reset)
		desc->current = desc->end;
	if (desc->current == 0 || desc->end == 0
			|| (desc->current >= desc->end))
	{
		if (desc->full_read)
			return (desc->full_read = 0);
		if (desc->current != 0 && desc->end != 0)
			free(desc->start);
		desc->start = (char*)malloc(sizeof(char) * BUFF_SIZE);
		desc->current = desc->start;
		desc->end = desc->current + BUFF_SIZE;
		res = read(fd, desc->current, BUFF_SIZE);
		if (res < 0)
			return (-1);
		if (res < BUFF_SIZE)
		{
			desc->full_read = 1;
			desc->end = desc->start + res;
		}
	}
	return (1);
}

char						*search_gnl(t_descriptor *c, int fd)
{
	char							*search;
	char							*b;
	int								bs;

	search = c->current;
	bs = 0;
	b = 0;
	while (*search != '\n')
	{
		search = ft_strnchr(c->current, '\n', (c->end - c->current));
		if (search == 0)
		{
			b = expand_write(c->current, (c->end - c->current), b, &bs);
			if (!malloc_or_use(fd, c, 1))
				break ;
			search = c->current;
		}
	}
	if (search)
	{
		b = expand_write(c->current, (search - c->current), b, &bs);
		c->current = search + 1;
	}
	b = expand_write("\0", 1, b, &bs);
	return (b);
}

t_descriptor				*find_or_add(t_descriptor **descriptor, int fd)
{
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	if (descriptor[fd])
		return (descriptor[fd]);
	else
	{
		descriptor[fd] = (t_descriptor*)malloc(sizeof(t_descriptor));
		descriptor[fd]->start = 0;
		descriptor[fd]->current = 0;
		descriptor[fd]->end = 0;
		descriptor[fd]->full_read = 0;
		return (descriptor[fd]);
	}
}

int							get_next_line(const int fd, char **line)
{
	static t_descriptor				**descriptors;
	t_descriptor					*curr;

	if (!descriptors)
		descriptors = (t_descriptor**)
			ft_memalloc(sizeof(t_descriptor*) * DESCRIPTOR_SIZE);
	curr = find_or_add(descriptors, fd);
	if (!curr || !line)
		return (-1);
	if (malloc_or_use(fd, curr, 0))
	{
		if (curr->current >= curr->end)
			return (curr->full_read = 0);
		*line = search_gnl(curr, fd);
		return (1);
	}
	return (0);
}
