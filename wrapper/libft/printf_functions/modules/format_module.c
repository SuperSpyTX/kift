/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_module.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 22:43:59 by jkrause           #+#    #+#             */
/*   Updated: 2017/08/24 22:43:04 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*prefix(t_input *in, char *str, char *result, int *bsize)
{
	char				*tmp;

	tmp = 0;
	if ((in->flag_alt_mode && LC(in->type, 'x') && ft_strlen(str) == 0)
			|| (*str == '0' && !LC(in->type, 'd')
				&& in->error != -9) || LC(in->type, 'u'))
		return (expand_write("", 0, result, bsize));
	if (in->length_extended == 4)
		result = expand_write("-", 1, result, bsize);
	else if (in->module == 'i' && in->flag_all_signs_char != 0)
	{
		tmp = ft_strnew(1);
		tmp[0] = in->flag_all_signs_char;
		result = expand_write(tmp, 1, result, bsize);
	}
	else if (in->module == 'i' && in->flag_alt_mode == 1 && CMP(in->type, 'x'))
		result = expand_write("0x", 2, result, bsize);
	else if (in->module == 'i' && in->flag_alt_mode == 1 && CMP(in->type, 'X'))
		result = expand_write("0X", 2, result, bsize);
	else if (in->module == 'i' && in->flag_alt_mode == 1
			&& CMP(in->type, 'o') && *str != '0')
		result = expand_write("0", 1, result, bsize);
	if (tmp)
		free(tmp);
	return (result);
}

int					prefixstr(t_input *in, char *str)
{
	int					rsize;
	char				*result;

	result = 0;
	rsize = 0;
	result = prefix(in, str, result, &rsize);
	free(result);
	return (rsize);
}

char				*precise(t_input *in, char *str, char *result, int *bsize)
{
	int					precision;
	int					length;

	length = in->output_length;
	precision = (in->precision == INT_MIN ? INT_MIN : in->precision);
	if (precision != INT_MIN)
	{
		if (precision <= 0 && in->module != 'i')
		{
			result = prefix(in, str, result, bsize);
			length = precision + length;
		}
		else if (precision > 0 && in->module == 'i')
		{
			result = prefix(in, str, result, bsize);
			result = expand_pad('0', precision, result, bsize);
		}
		else
			result = prefix(in, str, result, bsize);
	}
	else if (in->error != 3)
		result = prefix(in, str, result, bsize);
	result = expand_write(str, length, result, bsize);
	return (result);
}

char				*width(t_input *in, char *str, char *result, int *bsize)
{
	int					width;
	int					length;

	length = in->output_length;
	if (length > 0 || CMP(in->type, 'c')
			|| (in->precision != INT_MIN && CMP(in->module, 'i')))
		length = prefixstr(in, str)
			+ (CMP(in->type, 'c') && length < 1 ? 1 : 0)
			+ (((in->precision != INT_MIN && in->module != 'i') ||
				(in->module == 'i' && in->precision > 0)) ? in->precision : 0)
			+ length;
	width = in->width - length;
	if (width > 0 && !in->flag_left_justify
			&& in->precision == INT_MIN
			&& in->flag_zero_pad && in->module == 'i')
	{
		result = prefix(in, str, result, bsize);
		in->error = 3;
		result = expand_pad('0', width, result, bsize);
	}
	else if (width > 0)
		result = expand_pad(' ', width, result, bsize);
	return (result);
}

int					format_module(t_input *in, char *str)
{
	char				*result;
	int					bsize;

	result = 0;
	bsize = 0;
	if (!in->output_length)
		in->output_length = ft_strlen(str);
	if (in->precision != INT_MIN)
		in->precision -= in->output_length;
	if (in->flag_left_justify)
	{
		result = precise(in, str, result, &bsize);
		result = width(in, str, result, &bsize);
	}
	else if (CMP(in->type, 'c') && in->output_length == 0)
		result = width(in, str, result, &bsize);
	else
	{
		result = width(in, str, result, &bsize);
		result = precise(in, str, result, &bsize);
	}
	result = expand_write("\0", 1, result, &bsize);
	write_module(result, 1, 0);
	(in->output_length == 0 && LC(in->type, 'c') ? write_module("", 0, 1) : 0);
	return (1);
}
