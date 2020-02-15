/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:29:38 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/15 09:23:17 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_execution.h"

static int	exec_and_or(t_sh_data *shd, t_and_or *and_or)
{
	int	ret;

	ret = 0;
	if (and_or->left)
		ret = exec_and_or(shd, and_or->left);
	if (and_or->type == AO_TYPE_NONE)
		ret = exec_command(shd, and_or->right);
	else if (and_or->type == AO_TYPE_AND)
		ret = (ret || exec_command(shd, and_or->right));
	else if (and_or->type == AO_TYPE_OR)
		ret = (ret && exec_command(shd, and_or->right));
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
