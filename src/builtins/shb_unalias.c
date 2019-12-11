/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_unalias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:25:05 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:06:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"
#include "sh_data.h"

static char	**unalias_opt(t_sh_data *shd, int argc, char **argv)
{
	t_optdata	od;
	int			unset_all;

	unset_all = 0;
	init_getopt(&od, "a", 0, 0);
	while (ft_getopt(argc, argv, &od) != -1)
		unset_all = 1;
	if (unset_all)
		ft_lstdel(&shd->alias, shvar_del);
	return (argv + od.optind);
}

int			shb_unalias(char **argv, t_sh_data *shd)
{
	int			ret;
	int			argc;

	ret = 1;
	if ((argc = ft_wtlen(argv)) == 1)
		ft_putstr_fd("unalias: no argument\n", 2);
	else
	{
		ret = 0;
		argv = unalias_opt(shd, argc, argv);
		while (*argv)
		{
			if (get_shvar(*argv, shd->alias))
				ft_lst_remove_if(&shd->alias, *argv, name_shvar_cmp);
			else
			{
				ft_dprintf(2, "unalias: %s: not found\n", *argv);
				ret = 1;
			}
			++argv;
		}
	}
	return (ret);
}
