/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_module.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 14:27:21 by jkrause           #+#    #+#             */
/*   Updated: 2017/08/22 15:23:08 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void				check_flags(t_input *input, char **fmt)
{
	char				fc;

	fc = **fmt;
	while (CMP(fc, '-') || CMP(fc, '+') || CMP(fc, ' ')
			|| CMP(fc, '0') || CMP(fc, '#'))
	{
		if (fc == ' ')
			input->flag_all_signs_char != '+'
				? input->flag_all_signs_char = ' ' : 0;
		if (fc == '+')
			input->flag_all_signs_char = '+';
		if (fc == '#')
			input->flag_alt_mode = 1;
		if (fc == '0')
			input->flag_zero_pad = 1;
		if (fc == '-')
			input->flag_left_justify = 1;
		*fmt += 1;
		fc = **fmt;
	}
}

void				check_widthcision(t_input *input, char **fmt)
{
	int					tmp;
	char				fc;

	tmp = 0;
	fc = **fmt;
	while ((fc >= '0' && fc <= '9') || fc == '.' || fc == '*')
	{
		input->asterisks += (fc == '*' ? 1 : 0);
		if (fc == '.')
		{
			input->width = tmp;
			input->precision = 0;
			tmp = 0;
			if (*(*fmt + 1) < '0' || *(*fmt + 1) > '9')
				return (void)(*fmt += 1);
		}
		else
			tmp += fc - '0';
		if (*(*fmt + 1) >= '0' && *(*fmt + 1) <= '9')
			tmp *= 10;
		*fmt += 1;
		fc = **fmt;
	}
	input->width != INT_MIN ? input->precision = tmp : 0;
	input->width == INT_MIN ? input->width = tmp : 0;
}

void				check_length_hijacked(t_input *input, char **fmt)
{
	char				fc;

	fc = **fmt;
	if (CMP(fc, 'h') || CMP(fc, 'l') || CMP(fc, 'j')
			|| CMP(fc, 'z') || CMP(fc, 't'))
	{
		if (fc == 'h' || fc == 'l')
			if (*(*fmt + 1) == 'h' || *(*fmt + 1) == 'l')
				input->length_extended = 1;
		input->length = fc;
		*fmt += input->length_extended ? 2 : 1;
		fc = **fmt;
	}
	if (**fmt == '*')
	{
		input->asterisks += 1;
		*fmt += 1;
	}
}

int					parse_module(t_input *input, void *ptr)
{
	char				*alpha;
	char				*fmt;

	alpha = "sSpdDioOuUxXcCn%";
	input->width = INT_MIN;
	input->precision = INT_MIN;
	input->asterisks = 0;
	fmt = (char*)ptr + 1;
	check_flags(input, &fmt);
	check_widthcision(input, &fmt);
	check_length_hijacked(input, &fmt);
	while (*alpha != '\0')
	{
		if (*alpha == *fmt)
		{
			input->type = *alpha;
			input->error = 0;
			break ;
		}
		alpha += 1;
	}
	if (!input->type)
		input->error = 1;
	input->input_length = (fmt - (char*)ptr);
	return (1);
}
