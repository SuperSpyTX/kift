/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 20:16:43 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/26 12:02:28 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

char				*expand_pad(char c, int repeat,
						char *result, int *bsize);
void				*expand_write(void *dst, int dstlen,
						void *src, int *srcsize);
void				*expand_get_next_line_until(int fd, void *(*f)(char*));
#endif
