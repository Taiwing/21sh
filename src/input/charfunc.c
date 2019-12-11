/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 17:10:47 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:09:45 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charfunc.h"

char	* const g_multibyte_chars[8] = {
	"\033[A",
	"\033[B",
	"\033[C",
	"\033[D",
	"\033[H",
	"\033[F",
	"\033[3~",
	NULL
};

int		(* const g_charfunc[256])(t_input_data *idat, t_sh_data *shd) = {
	[0] = discard_input,
	['\003'] = reset_input,
	['\004'] = end_of_transmission,
	['\t'] = tab_completion,
	['\n'] = new_line,
	[UP_ARROW] = last_cmd,
	[DOWN_ARROW] = next_cmd,
	[LEFT_ARROW] = move_left,
	[RIGHT_ARROW] = move_right,
	[HOME_KEY] = move_beg,
	[END_KEY] = move_end,
	[DELETE_KEY] = forwd_delete,
	[' ' ... '~'] = insert_char,
	['\177'] = back_delete,
};
