/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphinx-wrapper.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:05:54 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/11 23:01:45 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHINX_WRAPPER_H
# define SPHINX_WRAPPER_H
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <pocketsphinx.h>

# define POCKETSPHINX_DEBUG 0

# define FREE_ARR free(conf[1]); free(conf[3]); free(conf[5]);

int						test_function(void);
char					*wrap_str_test(char *buffer);
ps_decoder_t			*init_sphinx(char *base);
char					*process_data(ps_decoder_t *ptr,
							int16_t *data, size_t size, int code);

#endif
