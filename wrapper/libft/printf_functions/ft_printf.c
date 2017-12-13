/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 11:15:43 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/02 15:06:29 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_input				*search(char *fmt)
{
	char				*search;
	t_input				*parsed;

	search = fmt;
	parsed = 0;
	while (*search != '\0')
	{
		search = ft_strchr(fmt, '%');
		if (search == 0)
			break ;
		parsed = (t_input*)ft_memalloc(sizeof(t_input));
		module_call(PARSEMODULE_PARSE, parsed, search);
		parsed->original = search;
		return (parsed);
	}
	return (0);
}

int					ft_printf(const char *fmt, ...)
{
	va_list				start;
	t_input				*iflag;
	char				*current;

	current = (char*)fmt;
	module_init();
	g_modules[WRITEMODULE_WRITE] = (t_module)bufferwrite_module_write;
	g_modules[WRITEMODULE_FLUSH] = (t_module)bufferwrite_module_flush;
	va_start(start, fmt);
	while ((iflag = search(current)) != 0)
	{
		write_module(ft_strsub(current, 0, (iflag->original - current)), 1, 0);
		module_call(ASTERISKMODULE_PARSE, iflag, &start);
		if (iflag->error || module_call(iflag->type, iflag, &start) == 0)
		{
			write_flush(-1);
			free(iflag);
			return (0);
		}
		current += (iflag->original - current) + iflag->input_length + 1;
		free(iflag);
	}
	write_module(current, 0, 0);
	va_end(start);
	return (write_flush(0));
}

char				*ft_sprintf(const char *fmt, ...)
{
	va_list				start;
	t_input				*iflag;
	char				*current;

	current = (char*)fmt;
	module_init();
	g_modules[WRITEMODULE_WRITE] = (t_module)bufferstring_module_write;
	va_start(start, fmt);
	while ((iflag = search(current)) != 0)
	{
		write_module(ft_strsub(current, 0, (iflag->original - current)), 1, 0);
		module_call(ASTERISKMODULE_PARSE, iflag, &start);
		if (iflag->error || module_call(iflag->type, iflag, &start) == 0)
		{
			write_flush(-1);
			free(iflag);
			return (0);
		}
		current += (iflag->original - current) + iflag->input_length + 1;
		free(iflag);
	}
	write_module(current, 0, 0);
	write_module("", 0, 1);
	va_end(start);
	return (bufferstring_module_retrieve());
}
