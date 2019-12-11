/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 02:55:18 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:06:12 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"
#include "sh_data.h"

int	shb_setenv(char **argv, t_sh_data *shd)
{
	int	argc;

	if ((argc = ft_wtlen(argv)) == 1)
		ft_putstr_fd("setenv: no argument\n", 2);
	else if (argc > 3)
		ft_putstr_fd("setenv: too many arguments\n", 2);
	else
	{
		set_shvar(argv[1], argv[2], &shd->env, ENV_VAR);
		if (!ft_strcmp(argv[1], "PATH"))
		{
			ft_wtfree(shd->path);
			shd->path = ft_strsplit(get_shvar_val("PATH", shd->env), ':');
		}
		return (0);
	}
	return (1);
}
