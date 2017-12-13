/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:14:28 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/11 02:42:56 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char				*ft_strstr(const char *big, const char *little)
{
	int charsmud;
	int i;

	i = -1;
	if (little[0] == '\0')
		return (char*)(big);
	while (big[++i] != '\0')
	{
		charsmud = -1;
		while (little[++charsmud] != '\0')
		{
			if (little[charsmud] != big[i + charsmud])
				break ;
			if (little[charsmud + 1] == '\0')
				return (char*)(big + i);
		}
	}
	return (0);
}
