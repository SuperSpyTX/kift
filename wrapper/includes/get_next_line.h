/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 01:54:57 by jkrause           #+#    #+#             */
/*   Updated: 2017/07/15 17:02:40 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE 2
# endif

# ifndef DESCRIPTOR_SIZE
#  define DESCRIPTOR_SIZE 9999
# endif

# include "libft.h"
# include "limits.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <fcntl.h>

typedef struct		s_descriptor
{
	char			*start;
	char			*current;
	char			*end;
	int				full_read;
}					t_descriptor;

int					get_next_line(const int fd, char **line);

#endif
