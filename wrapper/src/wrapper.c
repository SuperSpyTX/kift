/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 18:00:51 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/11 23:20:36 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

/*
** "God has left us" - Joe
** "God is dead and we killed him" - Aneesh
** "There is no god here" - Logan
*/

ps_decoder_t					*init_sphinx(char *base)
{
	ps_decoder_t		*ps;
	cmd_ln_t			*config;
	char				*conf[8];
	int					debug;

	debug = POCKETSPHINX_DEBUG;
	ps = NULL;
	if (!base)
		base = "sphinxbase/share/pocketsphinx/model";
	conf[0] = "-hmm";
	conf[1] = ft_sprintf("%s/en-us/en-us", base);
	conf[2] = "-lm";
	conf[3] = ft_sprintf("%s/en-us/en-us.lm.bin", base);
	conf[4] = "-dict";
	conf[5] = ft_sprintf("%s/en-us/cmudict-en-us.dict", base);
	if (!debug)
	{
		conf[6] = "-logfn";
		conf[7] = "/dev/null";
	}
	config = cmd_ln_parse_r(NULL, ps_args(), (debug ? 6 : 8), conf, FALSE);
	FREE_ARR;
	ps = ps_init(config);
	return (ps);
}

/*
** TODO: Rewrite this horrible code.
*/

char							*process_data(ps_decoder_t *ptr,
									int16_t *data, size_t size, int code)
{
	int							res;
	int							score;

	(void)size;
	(void)ptr;
	if (code == 0)
		res = ps_start_utt(ptr);
	else if (code == 1)
		res = ps_process_raw(ptr, data, size, FALSE, FALSE);
	else if (code == 2)
		res = ps_end_utt(ptr);
	if (code == 2)
		return ((char *)ps_get_hyp(ptr, &score));
	return (0);
}
