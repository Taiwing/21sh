/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:29:38 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:07:27 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_execution.h"

static int	exec_and_or(t_sh_data *shd, t_and_or *and_or)
{
	int	ret;

	while (and_or)
	{
		ret = exec_command(shd, and_or->cur);
		if ((and_or->type == AO_TYPE_AND && ret)
			|| (and_or->type == AO_TYPE_OR && !ret)
			|| and_or->type == AO_TYPE_NONE)
			break ;
		and_or = and_or->next;
	}	
	return (ret);
}

void		sh_execution(t_sh_data *shd, t_cmd_list *cmd_list)
{
	while (cmd_list)
	{
		shd->cmd_exit = exec_and_or(shd, cmd_list->cur);
		cmd_list = cmd_list->next;
	}
}
