/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_functions_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:01:04 by yforeau           #+#    #+#             */
/*   Updated: 2019/05/03 18:58:09 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charfunc.h"

int	move_end(t_input_data *idat, t_ms_data *msd)
{
	if (idat->lst && (idat->lst->next || idat->bol))
	{
		ft_strcpy(idat->c, g_multibyte_chars[RIGHT_ARROW - 11]);
		while (idat->lst->next || idat->bol)
			move_right(idat, msd);
	}
	return (CONTINUE_INPUT);
}

int	forwd_delete(t_input_data *idat, t_ms_data *msd)
{
	(void)msd;
	if (idat->lst && (idat->lst->next || idat->bol))
	{
		ft_putstr_fd(" \10", 0);
		if (idat->bol)
			dllst_remove_back(&idat->lst);
		else
			dllst_remove_forwd(&idat->lst);
		if (idat->lst)
		{
			if (idat->bol)
				reprint_line(idat->lst);
			else if (idat->lst->next)
				reprint_line(idat->lst->next);
		}
	}
	return (CONTINUE_INPUT);
}

int	insert_char(t_input_data *idat, t_ms_data *msd)
{
	if (idat->cursor_pos[X] == msd->term_width)
	{
		idat->cursor_pos[X] = 1;
		++idat->cursor_pos[Y];
	}
	else
		++idat->cursor_pos[X];
	write(0, idat->c, 1);
	if (!idat->bol)
		dllst_insert_forwd(&idat->lst, *idat->c);
	else
		dllst_insert_back(&idat->lst, *idat->c);
	if (idat->lst->next)
		reprint_line(idat->lst->next);
	idat->bol = 0;
	return (CONTINUE_INPUT);
}

int	back_delete(t_input_data *idat, t_ms_data *msd)
{
	if (!idat->bol)
	{
		if (!idat->lst->prev)
			idat->bol = 1;
		if (idat->cursor_pos[X] == 1)
		{
			--idat->cursor_pos[Y];
			idat->cursor_pos[X] = msd->term_width;
		}
		else
			--idat->cursor_pos[X];
		if (!idat->lst->prev && idat->cursor_pos[X] != msd->term_width)
			ft_putstr_fd("\010 \010", 0);
		else
			write(0, "\010", 1);
		dllst_remove_back(&idat->lst);
		if (idat->lst)
			reprint_line(idat->bol ? idat->lst : idat->lst->next);
	}
	return (CONTINUE_INPUT);
}
