/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 16:44:19 by jkrause           #+#    #+#             */
/*   Updated: 2017/07/22 17:30:13 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_putnum(int num, int base, char *buf, int *size)
{
	char			*alpha;
	int				max;
	char			pls;

	alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	pls = 0;
	max = base - 1;
	if (num < 0)
		num *= -1;
	if (num > max)
		pls = alpha[0];
	else
	{
		pls = alpha[num];
		buf = (char*)expand_write(&pls, 1, buf, size);
	}
	return (buf);
}

static char			*whenlifebreaksdown(int num, int base, char *buf, int *size)
{
	if (num >= base || num <= -base)
	{
		buf = whenlifebreaksdown(num / base, base, buf, size);
		buf = whenlifebreaksdown(num % base, base, buf, size);
	}
	else
		return (ft_putnum(num, base, buf, size));
	return (buf);
}

char				*ft_itoa_base(int value, int base)
{
	char			*ha;
	int				*size;

	ha = ft_strnew(1);
	size = ft_memalloc(sizeof(int*));
	if (!ha || !size)
		return (0);
	if (value < 0 && base == 10)
	{
		ha[0] = '-';
		*size = 1;
	}
	ha = whenlifebreaksdown(value, base, ha, size);
	ha = expand_write("\0", 1, ha, size);
	return (ha);
}
