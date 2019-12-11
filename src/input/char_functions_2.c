/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:01:02 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:09:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "charfunc.h"
#include "input_history.h"

int	last_cmd(t_input_data *idat, t_sh_data *shd)
{
	if ((size_t)idat->hi < shd->hist.size)
	{
		save_current_line(idat, &shd->hist);
		++idat->hi;
		restore(idat, &shd->hist, shd);
	}
	return (CONTINUE_INPUT);
}

int	next_cmd(t_input_data *idat, t_sh_data *shd)
{
	if (idat->hi)
	{
		save_current_line(idat, &shd->hist);
		--idat->hi;
		restore(idat, &shd->hist, shd);
	}
	return (CONTINUE_INPUT);
}

int	move_left(t_input_data *idat, t_sh_data *shd)
{
	if (idat->lst && !idat->bol)
	{
		if (idat->lst->prev)
			idat->lst = idat->lst->prev;
		else
			idat->bol = 1;
		write(0, idat->c, 3);
		if (idat->cursor_pos[X] == 1)
		{
			--idat->cursor_pos[Y];
			idat->cursor_pos[X] = shd->term_width;
		}
		else
			--idat->cursor_pos[X];
	}
	return (CONTINUE_INPUT);
}

int	move_right(t_input_data *idat, t_sh_data *shd)
{
	if (idat->lst)
	{
		if (!idat->bol)
		{
			if (!idat->lst->next)
				return (CONTINUE_INPUT);
			else
				idat->lst = idat->lst->next;
		}
		idat->bol = 0;
		write(0, idat->c, 3);
		if (idat->cursor_pos[X] == shd->term_width)
		{
			++idat->cursor_pos[Y];
			write(0, g_multibyte_chars[DOWN_ARROW - 11], 3);
			while (idat->cursor_pos[X] > 1)
			{
				--idat->cursor_pos[X];
				write(0, g_multibyte_chars[LEFT_ARROW - 11], 3);
			}
		}
		else
			++idat->cursor_pos[X];
	}
	return (CONTINUE_INPUT);
}

int	move_beg(t_input_data *idat, t_sh_data *shd)
{
	ft_strcpy(idat->c, g_multibyte_chars[LEFT_ARROW - 11]);
	while (!idat->bol)
		move_left(idat, shd);
	return (CONTINUE_INPUT);
}
