/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:14:36 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:20:40 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_data.h"
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

int			shb_exit(char **argv, t_sh_data *shd)
{
	int	ret;

	if (!argv[1])
		ret = shd->cmd_exit;
	else if (isnumstring(argv[1]))
		ret = ft_atoi(argv[1]);
	else
	{
		ft_putstr_fd(SHELL_NAME": exit: numeric argument required\n", 2);
		return (1);
	}
	if (ft_wtlen(argv) > 2)
	{
		ft_putstr_fd(SHELL_NAME": exit: too many arguments\n", 2);
		return (1);
	}
	flush_history(&shd->hist, shd->cmd_c, get_shvar_val("HOME", shd->env));
	ft_exit(NULL, ret);
	return (0);
}
