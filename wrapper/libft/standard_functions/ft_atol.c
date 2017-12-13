/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 11:22:00 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/23 13:41:46 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				trim_space(const char *str)
{
	int				i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

long long				ft_atol(const char *str)
{
	long long		num;
	long long		i;
	int				neg;

	num = 0;
	neg = 0;
	i = trim_space(str) - 1;
	if (str[i + 1] == '-')
	{
		i++;
		neg = 1;
	}
	else if (str[i + 1] == '+')
		i++;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (neg == 1 ? -num : num);
		num += str[i] - '0';
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			num *= 10;
	}
	return (neg == 1 ? -num : num);
}
