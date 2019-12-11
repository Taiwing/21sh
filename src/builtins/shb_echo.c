/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:19:54 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:04:55 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_data.h"

int	shb_echo(char **argv, t_sh_data *shd)
{
	t_optdata	od;
	int			i;
	int			argc;
	int			no_newline;

	(void)shd;
	no_newline = 0;
	argc = ft_wtlen(argv);
	init_getopt(&od, "n", 0, 0);
	while (ft_getopt(argc, argv, &od) != -1)
		no_newline = 1;
	argv += od.optind;
	i = -1;
	while (argv[++i])
	{
		if (ft_printf("%s%s", argv[i], argv[i + 1] ? " " : "") == -1)
			return (1);
	}
	if (!no_newline && ft_printf("\n") == -1)
		return (1);
	return (0);
}
