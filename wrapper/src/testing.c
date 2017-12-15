/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:05:37 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/13 15:57:58 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int						test_function(void)
{
	return (-1337);
}

char					*wrap_str_test(char *buffer)
{
	(void)ps_init(0);
	return (ft_sprintf("PLS: %s", buffer));
}

int						str_array_test(char **buffer)
{
	int					i;

	i = -1;
	while (buffer[++i] != 0)
		ft_printf("ARRAY TEST \"%s\"\n", buffer[i]);
	return (1);
}
