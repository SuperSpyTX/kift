/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 06:45:15 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/19 16:42:42 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t charsmud;
	size_t i;

	i = -1;
	if (little[0] == '\0')
		return (char*)(big);
	while (big[++i] != '\0')
	{
		charsmud = -1;
		while (little[++charsmud] != '\0')
		{
			if ((i + charsmud) >= len)
				break ;
			if (little[charsmud] != big[i + charsmud])
				break ;
			if (little[charsmud + 1] == '\0')
				return (char*)(big + i);
		}
	}
	return (0);
}
