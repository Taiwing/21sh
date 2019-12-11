/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msb_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:14:36 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/22 10:14:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_data.h"
#include "t_shvar.h"

static int	isnumstring(char *str)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

int			msb_exit(char **argv, t_ms_data *msd)
{
	int	ret;

	if (!argv[1])
		ret = msd->cmd_exit;
	else if (isnumstring(argv[1]))
		ret = ft_atoi(argv[1]);
	else
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		return (1);
	}
	if (ft_wtlen(argv) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	flush_history(&msd->hist, msd->cmd_c, get_shvar_val("HOME", msd->env));
	ft_exit(NULL, ret);
	return (0);
}
