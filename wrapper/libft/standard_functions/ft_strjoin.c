/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:02:22 by jkrause           #+#    #+#             */
/*   Updated: 2017/06/20 17:02:43 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	int				s1l;
	int				s2l;

	if (!s1 || !s2)
		return (0);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	newstr = ft_strnew(s1l + s2l);
	if (!newstr)
		return (0);
	ft_strcat(newstr, s1);
	ft_strcat(newstr, s2);
	return (newstr);
}
