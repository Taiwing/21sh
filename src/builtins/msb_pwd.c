/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msb_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:33:34 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 12:16:45 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_data.h"
#include "t_shvar.h"
#include <sys/syslimits.h>

int	msb_pwd(char **argv, t_ms_data *msd)
{
	char	curdir[PATH_MAX];

	(void)argv;
	(void)msd;
	if (!getcwd(curdir, PATH_MAX))
	{
		set_shvar("PWD", NULL, &msd->env, ENV_VAR);
		return (1);
	}
	ft_printf("%s\n", curdir);
	set_shvar("PWD", curdir, &msd->env, ENV_VAR);
	return (0);
}
