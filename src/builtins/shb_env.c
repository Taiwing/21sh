/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:17:06 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:05:22 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"
#include "sh_execution.h"

static void		set_tmp_env(char ***argv, t_sh_data *shd, t_list **backup)
{
	t_shvar	newvar;
	t_shvar	*oldvar;

	while (str_to_env(&newvar, **argv))
	{
		if (!(oldvar = get_shvar(newvar.name, shd->env)))
		{
			newvar.type = ENV_LOCAL_VAR;
			ft_lst_sorted_insert(&shd->env, ft_lstnew((void *)&newvar,
				sizeof(t_shvar)), shvar_cmp);
		}
		else
		{
			ft_lst_sorted_insert(backup, ft_lstnew((void *)oldvar,
				sizeof(t_shvar)), shvar_cmp);
			oldvar->type = ENV_LOCAL_VAR;
			oldvar->name = newvar.name;
			oldvar->value = newvar.value;
		}
		++(*argv);
	}
}

static int		is_local_env(void *ref, void *content)
{
	t_shvar	*svar;

	(void)ref;
	svar = (t_shvar *)content;
	if (svar->type != ENV_LOCAL_VAR)
		return (1);
	shvar_del(content, 0);
	return (0);
}

static void		reset_env(t_sh_data *shd, t_list *env_backup, int empty_env)
{
	t_list	*lst;

	if (empty_env)
	{
		ft_lstdel(&shd->env, shvar_del);
		shd->env = env_backup;
		env_backup = NULL;
	}
	ft_lst_remove_if(&shd->env, NULL, is_local_env);
	ft_lst_remove_if(&env_backup, NULL, is_local_env);
	while (env_backup)
	{
		lst = env_backup;
		env_backup = env_backup->next;
		lst->next = NULL;
		ft_lst_sorted_insert(&shd->env, lst, shvar_cmp);
	}
}

static void		exec_with_tmp_env(char **argv, t_sh_data *shd, int empty_env)
{
	char	**path_backup;
	t_list	*env_backup;

	env_backup = NULL;
	path_backup = NULL;
	if (empty_env)
	{
		env_backup = shd->env;
		shd->env = NULL;
	}
	set_tmp_env(&argv, shd, &env_backup);
	if (get_shvar("PATH", env_backup))
	{
		path_backup = shd->path;
		shd->path = ft_strsplit(get_shvar_val("PATH", shd->env), ':');
	}
//	if (*argv)
//		sh_execution(shd, &argv, CMD_KEEP);
	reset_env(shd, env_backup, empty_env);
	if (path_backup || (!get_shvar_val("PATH", shd->env) && shd->path))
	{
		ft_wtfree(shd->path);
		shd->path = path_backup;
	}
}

int				shb_env(char **argv, t_sh_data *shd)
{
	t_optdata	od;
	int			argc;
	char		**env;
	int			empty_env;

	empty_env = 0;
	if ((argc = ft_wtlen(argv)) == 1)
	{
		if ((env = list_to_env(shd->env)))
		{
			ft_print_words_tables(env);
			ft_wtfree(env);
		}
	}
	else
	{
		return (0); //TODO: remove this when exec_with_tmp_env is fixed
		init_getopt(&od, "i", 0, 0);
		while (ft_getopt(argc, argv, &od) != -1)
			empty_env = 1;
		argv += od.optind;
		if (*argv)
			exec_with_tmp_env(argv, shd, empty_env);
	}
	return (0);
}
