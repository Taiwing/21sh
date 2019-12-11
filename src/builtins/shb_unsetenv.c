/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 02:55:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:06:35 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"
#include "sh_data.h"

int	shb_unsetenv(char **argv, t_sh_data *shd)
{
	int		argc;
	t_shvar	*svar;

	if ((argc = ft_wtlen(argv)) == 1)
		ft_putstr_fd("unsetenv: no argument\n", 2);
	else if (argc > 2)
		ft_putstr_fd("unsetenv: too many arguments\n", 2);
	else if (!(svar = get_shvar(argv[1], shd->env)))
		ft_dprintf(2, "unsetenv: '%s' is not set in current environment\n",
			argv[1]);
	else
	{
		ft_lst_remove_if(&shd->env, argv[1], name_shvar_cmp);
		if (!ft_strcmp(argv[1], "PATH"))
		{
			ft_wtfree(shd->path);
			shd->path = NULL;
		}
		return (0);
	}
	return (1);
}
