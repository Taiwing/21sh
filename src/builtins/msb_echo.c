/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msb_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:19:54 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/12 17:56:17 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_data.h"

int	msb_echo(char **argv, t_ms_data *msd)
{
	t_optdata	od;
	int			i;
	int			argc;
	int			no_newline;

	(void)msd;
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
