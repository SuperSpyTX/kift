/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 18:00:51 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/14 19:11:28 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

/*
** Much better.
*/

ps_decoder_t					*init_sphinx(char **args, int argc)
{
	ps_decoder_t		*ps;
	cmd_ln_t			*config;

	config = cmd_ln_parse_r(NULL, ps_args(), argc, args, FALSE);
	ps = ps_init(config);
	return (ps);
}

char							*process_voice_hypothesis(ps_decoder_t *ptr,
									int16_t *data, size_t size)
{
	int							res;
	int							score;

	res = ps_start_utt(ptr);
	res = ps_process_raw(ptr, data, size, FALSE, FALSE);
	res = ps_end_utt(ptr);
	return ((char *)ps_get_hyp(ptr, &score));
}
