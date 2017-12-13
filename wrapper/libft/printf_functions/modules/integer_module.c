/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_module.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:23:49 by jkrause           #+#    #+#             */
/*   Updated: 2017/08/24 19:08:18 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				*magic_convert(t_input *input, void *arg, int sign)
{
	t_magicnum		number;
	void			*casted;

	number = (t_magicnum)arg;
	if (CMP(input->length, 'l') || CMP(input->length, 't'))
		casted = (void*)(number.magic);
	else if (CMP(input->length, 'h') && !sign)
		casted = (void*)(input->length_extended
				? (intptr_t)number.uchar : (intptr_t)number.ushort);
	else if (CMP(input->length, 'h'))
		casted = (void*)(input->length_extended
				? (intptr_t)number.schar : (intptr_t)number.sshort);
	else if (CMP(input->length, 'j'))
		casted = (void*)number.intmax;
	else if (CMP(input->length, 'z') && !sign)
		casted = (void*)number.usize_t;
	else if (CMP(input->length, 'z'))
		casted = (void*)number.sssize_t;
	else if (!sign)
		casted = (void*)(intptr_t)number.uint;
	else
		casted = (void*)(intptr_t)number.sint;
	return (casted);
}

int					integer_conv(t_input *input, va_list ptr,
						int base, char *alpha)
{
	char			*buffer;
	void			*number;
	int				sign;

	sign = 1;
	if (input->type != 'd' && input->type != 'i'
			&& input->type != 'D' && input->type != 'I')
		sign = 0;
	number = magic_convert(input, va_arg(ptr, void*), sign);
	if (CMP(input->type, 'u') || base != 10)
		sign = 0;
	buffer = ft_ltostr_base(number, base, alpha, sign);
	input->module = 'i';
	if (buffer[0] == '-')
	{
		input->length_extended = 4;
		module_call(FORMATMODULE_FORMAT, input, buffer + 1);
	}
	else if (buffer[0] == '0' && input->precision != INT_MIN)
		module_call(FORMATMODULE_FORMAT, input, "");
	else
		module_call(FORMATMODULE_FORMAT, input, buffer);
	free(buffer);
	return (1);
}

void				aliasing(t_input *input)
{
	if (CMP(input->type, 'D'))
	{
		input->length = 'l';
		input->type = 'd';
		input->length_extended = 0;
	}
	else if (CMP(input->type, 'p'))
	{
		input->length = 'l';
		input->type = 'x';
		input->error = -9;
		input->flag_alt_mode = 1;
		input->length_extended = 0;
	}
	else if (CMP(input->type, 'U'))
	{
		input->length = 'l';
		input->type = 'u';
	}
}

int					integer_module(t_input *input, va_list *ptr)
{
	aliasing(input);
	if (LC(input->type, 'd') || LC(input->type, 'u')
			|| LC(input->type, 'i'))
		return (integer_conv(input, *ptr, 10, "0123456789abcdef"));
	else if (CMP(input->type, 'x'))
		return (integer_conv(input, *ptr, 16, "0123456789abcdef"));
	else if (CMP(input->type, 'X'))
		return (integer_conv(input, *ptr, 16, "0123456789ABCDEF"));
	else if (LC(input->type, 'o'))
		return (integer_conv(input, *ptr, 8, "0123456789abcdef"));
	return (1);
}
