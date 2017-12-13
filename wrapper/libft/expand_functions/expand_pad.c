/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:25:52 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/14 01:35:01 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*expand_pad(char c, int repeat, char *result, int *bsize)
{
	char				*tmp;

	tmp = ft_strnew(repeat);
	ft_memset(tmp, c, repeat);
	result = expand_write(tmp, repeat, result, bsize);
	free(tmp);
	return (result);
}
