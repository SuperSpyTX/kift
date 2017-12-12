/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 03:12:20 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/11 03:13:46 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			putnum(int num, int fd)
{
	char		*alpha;
	int			max;

	alpha = "0123456789abcdef";
	max = 15;
	if (num < 0)
		num *= -1;
	if (num > max)
		ft_putchar_fd(alpha[0], fd);
	else
		ft_putchar_fd(alpha[num], fd);
}

static void			whenlifebreaksdown(int nb, int fd)
{
	if (nb >= 10 || nb <= -10)
	{
		whenlifebreaksdown(nb / 10, fd);
		whenlifebreaksdown(nb % 10, fd);
	}
	else
		putnum(nb, fd);
}

void				ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
	}
	whenlifebreaksdown(nb, fd);
}
