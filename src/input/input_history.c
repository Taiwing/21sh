/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 07:54:37 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:10:27 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_input.h"
#include "charfunc.h"
#include "terminal_cursor.h"

void		save_current_line(t_input_data *idat, t_sh_history *hist)
{
	char	*raw;

	if (!idat->hi)
		idat->buf = dllst_to_str(dllst_first(idat->lst));
	else
	{
		ft_memdel((void **)&hist->cmd[hist->size - idat->hi]);
		raw = dllst_to_str(dllst_first(idat->lst));
		hist->cmd[hist->size - idat->hi] = ft_stradd(&raw, "\n", 1);
	}
}

static void	erase_current_line(t_input_data *idat, t_sh_data *shd)
{
	if (!idat->lst)
		return ;
	move_end(idat, shd);
	while (!idat->bol)
		back_delete(idat, shd);
}

void		restore(t_input_data *idat, t_sh_history *hist, t_sh_data *shd)
{
	erase_current_line(idat, shd);
	if (!idat->hi && idat->buf)
	{
		idat->lst = dllst_last(str_to_dllst(idat->buf));
		ft_dprintf(0, "%s", idat->buf);
		get_curs_pos(idat->cursor_pos);
		idat->bol = idat->lst ? 0 : 1;
	}
	else if (idat->hi)
	{
		idat->lst = dllst_last(str_to_dllst(hist->cmd[hist->size - idat->hi]));
		if (idat->lst)
		{
			dllst_remove_back(&idat->lst);
			ft_dprintf(0, "%.*s",
				ft_strlen(hist->cmd[hist->size - idat->hi]) - 1,
				hist->cmd[hist->size - idat->hi]);
			get_curs_pos(idat->cursor_pos);
		}
		idat->bol = idat->lst ? 0 : 1;
	}
}
