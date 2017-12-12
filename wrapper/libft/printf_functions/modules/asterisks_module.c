/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisks_module.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 19:28:18 by jkrause           #+#    #+#             */
/*   Updated: 2017/08/21 23:03:50 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					asterisks_module(t_input *input, va_list *ptr)
{
	int					result;

	result = 0;
	if (input->asterisks > 1)
	{
		input->width = va_arg(*ptr, int);
		input->precision = va_arg(*ptr, int);
	}
	else if (input->asterisks > 0)
		input->width = va_arg(*ptr, int);
	return (0);
}
