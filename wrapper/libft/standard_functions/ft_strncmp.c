/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:00:57 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/21 13:27:53 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 1 && *s1 == *s2 && (*s1 || *s2))
	{
		(void)*s1++;
		(void)*s2++;
		n--;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
