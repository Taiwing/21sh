/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msb_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 02:55:18 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 12:18:20 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"
#include "ms_data.h"

int	msb_setenv(char **argv, t_ms_data *msd)
{
	int	argc;

	if ((argc = ft_wtlen(argv)) == 1)
		ft_putstr_fd("setenv: no argument\n", 2);
	else if (argc > 3)
		ft_putstr_fd("setenv: too many arguments\n", 2);
	else
	{
		set_shvar(argv[1], argv[2], &msd->env, ENV_VAR);
		if (!ft_strcmp(argv[1], "PATH"))
		{
			ft_wtfree(msd->path);
			msd->path = ft_strsplit(get_shvar_val("PATH", msd->env), ':');
		}
		return (0);
	}
	return (1);
}
