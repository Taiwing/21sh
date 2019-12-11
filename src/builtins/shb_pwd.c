/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:33:34 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:06:01 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_data.h"
#include "t_shvar.h"
#include <sys/syslimits.h>

int	shb_pwd(char **argv, t_sh_data *shd)
{
	char	curdir[PATH_MAX];

	(void)argv;
	(void)shd;
	if (!getcwd(curdir, PATH_MAX))
	{
		set_shvar("PWD", NULL, &shd->env, ENV_VAR);
		return (1);
	}
	ft_printf("%s\n", curdir);
	set_shvar("PWD", curdir, &shd->env, ENV_VAR);
	return (0);
}
