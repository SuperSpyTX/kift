/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltostr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 12:58:42 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/14 20:47:41 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long					ft_pow(long a, long b)
{
	long					res;

	res = a;
	while (b-- > 0)
		res *= a;
	return (res);
}

static void					*interpret_mulcast(void *ptr, long base,
								long mul, int sign)
{
	long					ln;

	if (!sign)
		return ((void*)((unsigned long)ptr / ft_pow(base, mul) % base));
	else
	{
		ln = ((long)ptr / ft_pow(base, mul) % base);
		if (ln < 0)
			return ((void*)(ln *= -1));
	}
	return ((void*)ln);
}

static long					mulsize(void *value, int base, int sign)
{
	long					size;
	long					cpy;
	unsigned long			ucpy;

	cpy = (long)value;
	ucpy = (unsigned long)value;
	size = 0;
	if (!sign)
	{
		while (ucpy >= (unsigned long)base)
		{
			ucpy /= base;
			size++;
		}
	}
	else
	{
		while (cpy >= (long)base || cpy <= (long)-base)
		{
			cpy /= base;
			size++;
		}
	}
	return (size);
}

char						*ft_ltostr_base(void *value, int base,
								char *alpha, int sign)
{
	char					*buffer;
	int						buffsize;
	unsigned long			ucpy;
	long					cpy;
	long					mul;

	buffsize = 0;
	ucpy = (unsigned long)value;
	cpy = (long)value;
	mul = mulsize(value, base, sign);
	buffer = (char*)malloc(sizeof(char) * mul + 3);
	if (cpy < 0 && sign)
		buffer[buffsize++] = '-';
	while (mul-- > 0)
		buffer[buffsize++] = alpha[(long)interpret_mulcast(value, base,
				mul, sign)];
	buffer[buffsize++] = alpha[((sign && cpy < 0 ? -cpy : ucpy) % base)];
	buffer[buffsize++] = '\0';
	return (buffer);
}
