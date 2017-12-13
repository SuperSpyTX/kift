/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorywrite_module.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 19:35:47 by jkrause           #+#    #+#             */
/*   Updated: 2017/08/21 23:17:24 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					memorywrite_module(t_input *input, va_list *ptr)
{
	int				*intptr;

	(void)input;
	intptr = va_arg(*ptr, int*);
	if (ptr)
		*intptr = write_flush(-2);
	return (1);
}
