/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 08:07:13 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 13:54:51 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strrchr(const char *s, int c)
{
	int				lastoccurance;
	int				i;

	i = -1;
	lastoccurance = -1;
	while (s[++i] != '\0')
		if ((unsigned char)s[i] == (unsigned char)c)
			lastoccurance = i;
	if (c == 0)
		lastoccurance = i;
	return (lastoccurance != -1 ? (char*)(s + lastoccurance) : 0);
}
