/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:32:03 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:04:47 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_data.h"
#include "t_shvar.h"
#ifdef __APPLE__
# include <sys/syslimits.h>
#elif __linux
# include <linux/limits.h>
#endif

static int	change_dir(char **argv, t_sh_data *shd)
{
	char	*dir;

	if (!(dir = argv[1] ? argv[1] : get_shvar_val("HOME", shd->env)))
		ft_putstr_fd("cd: HOME is not set or has no value\n", 2);
	else if (argv[1] && !ft_strcmp(dir, "-") &&
		!(dir = get_shvar_val("OLDPWD", shd->env)))
		ft_putstr_fd("cd: OLDPWD is not set or has no value\n", 2);
	else if (!chdir(dir))
		return (0);
	else
	{
		if (access(dir, F_OK) == -1)
			ft_dprintf(2, "cd: %s: no such file or directory\n", dir);
		else
			ft_dprintf(2, "cd: %s: is not a directory\n", dir);
	}
	return (-1);
}

int			shb_cd(char **argv, t_sh_data *shd)
{
	int		argc;
	char	newdir[PATH_MAX];

	if ((argc = ft_wtlen(argv)) > 2)
	{
		ft_putstr_fd("cd: wrong number of argument\n", 2);
		return (1);
	}
	else if (change_dir(argv, shd) == -1)
		return (1);
	else if (!getcwd(newdir, PATH_MAX))
	{
		set_shvar("OLDPWD", get_shvar_val("PWD", shd->env), &shd->env, ENV_VAR);
		set_shvar("PWD", NULL, &shd->env, ENV_VAR);
		ft_putstr_fd("cd: could not get current working directory\n", 2);
		return (1);
	}
	else
	{
		set_shvar("OLDPWD", get_shvar_val("PWD", shd->env), &shd->env, ENV_VAR);
		set_shvar("PWD", newdir, &shd->env, ENV_VAR);
	}
	return (0);
}
