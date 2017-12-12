/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_next_line_until.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 12:02:04 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/26 12:02:06 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "get_next_line.h"

void					*expand_get_next_line_until(int fd, void *(*f)(char*))
{
	char					*line;
	void					*result;

	result = 0;
	line = 0;
	while (get_next_line(fd, &line) == 1)
	{
		result = f(line);
		free(line);
		if (result)
			return (result);
	}
	return (0);
}
