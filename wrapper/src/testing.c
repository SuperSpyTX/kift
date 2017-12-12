/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:05:37 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/11 17:43:12 by jkrause          ###   ########.fr       */
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
