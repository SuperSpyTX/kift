/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphinx-wrapper.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:05:54 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/14 17:16:36 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHINX_WRAPPER_H
# define SPHINX_WRAPPER_H
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <pocketsphinx.h>

int						test_function(void);
char					*wrap_str_test(char *buffer);
ps_decoder_t			*init_sphinx(char **args, int argc);
char					*process_voice_hypothesis(ps_decoder_t *ptr,
							int16_t *data, size_t size);
int						str_array_test(char **buffer);

#endif
