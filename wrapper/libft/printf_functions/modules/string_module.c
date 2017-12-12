/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_module.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 13:23:30 by jkrause           #+#    #+#             */
/*   Updated: 2017/08/24 22:41:19 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				write_conv(t_input *input, void *conv)
{
	int					ch;
	char				*str;

	ch = 0;
	str = 0;
	if (CMP(input->type, 'c'))
		ch = (int)conv;
	else
		str = (char*)conv;
	if (CMP(input->type, 'c'))
	{
		str = ft_strnew(1);
		str[0] = ch;
		input->module = 's';
		module_call(FORMATMODULE_FORMAT, input, str);
		free(str);
	}
	else if (str)
	{
		input->module = 's';
		module_call(FORMATMODULE_FORMAT, input, str);
	}
	else
		write_module("(null)", 0, 0);
}

char				*convert_wchar(wchar_t ch)
{
	char				*result;

	result = ft_strnew(4);
	if (ch <= 0x7FF)
		result[0] = (char)ch;
	else if (ch <= 0xFFFF)
	{
		result[0] = 0xE0 | ((ch >> 12) & 0x3F);
		result[1] = 0x80 | ((ch >> 6) & 0x3F);
		result[2] = 0x80 | (ch & 0x3F);
	}
	else if (ch <= 0x10FFFF)
	{
		result[0] = 0xF0 | ((ch >> 18) & 0x3F);
		result[1] = 0x80 | ((ch >> 12) & 0x3F);
		result[2] = 0x80 | ((ch >> 6) & 0x3F);
		result[3] = 0x80 | (ch & 0x3F);
	}
	return (result);
}

char				*write_wconv(t_input *input, void *conv)
{
	wchar_t				ch;
	wchar_t				*str;
	char				*result;
	char				*tmp;
	int					bsize;

	result = 0;
	bsize = 0;
	if (CMP(input->type, 'C'))
		ch = (wchar_t)conv;
	else
		str = (wchar_t*)conv;
	if (CMP(input->type, 'C'))
		result = convert_wchar(ch);
	else if (str)
		while (*str != '\0')
		{
			tmp = convert_wchar(*str++);
			result = expand_write(tmp, ft_strlen(tmp), result, &bsize);
			free(tmp);
		}
	else
		result = ft_strdup("(null)");
	input->output_length = bsize;
	return (result);
}

int					string_aliasing(t_input *input)
{
	if (CMP(input->type, '%'))
	{
		input->type = 's';
		input->precision = INT_MIN;
		write_conv(input, "%");
		return (1);
	}
	if (CMP(input->type, 's') && CMP(input->length, 'l'))
		input->type = 'S';
	return (0);
}

int					string_module(t_input *input, va_list *ptr)
{
	char				*result;

	if (string_aliasing(input))
		return (1);
	if (CMP(input->type, 'C') || CMP(input->type, 'S'))
	{
		result = write_wconv(input, va_arg(*ptr, void*));
		input->type = 's';
		write_conv(input, result);
		free(result);
	}
	else if (CMP(input->type, 'c') || CMP(input->type, 's'))
		write_conv(input, va_arg(*ptr, void*));
	return (1);
}
