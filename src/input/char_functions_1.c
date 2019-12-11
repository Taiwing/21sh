/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_functions_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:00:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 16:59:37 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charfunc.h"
#include "quotes.h"
#include "tab_completion.h"

int	discard_input(t_input_data *idat, t_ms_data *msd)
{
	(void)msd;
	(void)idat;
	return (CONTINUE_INPUT);
}

int	reset_input(t_input_data *idat, t_ms_data *msd)
{
	(void)msd;
	ft_memdel((void **)&idat->buf);
	dllst_del(dllst_first(idat->lst));
	idat->lst = NULL;
	write(0, "\n", 1);
	return (STOP_INPUT);
}

int	end_of_transmission(t_input_data *idat, t_ms_data *msd)
{
	(void)msd;
	if (!idat->lst && idat->qmode == NO_QUOTE)
	{
		ft_memdel((void **)&idat->buf);
		idat->buf = ft_strdup("exit\n");
		ft_putstr_fd("exit\n", 0);
		return (STOP_INPUT);
	}
	return (CONTINUE_INPUT);
}

int	tab_completion(t_input_data *idat, t_ms_data *msd)
{
	char	*part;
	int		completion;

	part = NULL;
	if ((completion = check_completion(idat, &part)))
		complete_input(completion, part, idat, msd);
	return (CONTINUE_INPUT);
}

int	new_line(t_input_data *idat, t_ms_data *msd)
{
	idat->lst = dllst_last(idat->lst);
	insert_char(idat, msd);
	ft_memdel((void **)&idat->buf);
	idat->buf = dllst_to_str(dllst_first(idat->lst));
	dllst_del(dllst_first(idat->lst));
	idat->lst = NULL;
	check_input(idat, msd);
	return (STOP_INPUT);
}
