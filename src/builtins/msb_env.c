/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msb_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:17:06 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 14:15:15 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"
#include "ms_execution.h"

static void		set_tmp_env(char ***argv, t_ms_data *msd, t_list **backup)
{
	t_shvar	newvar;
	t_shvar	*oldvar;

	while (str_to_env(&newvar, **argv))
	{
		if (!(oldvar = get_shvar(newvar.name, msd->env)))
		{
			newvar.type = ENV_LOCAL_VAR;
			ft_lst_sorted_insert(&msd->env, ft_lstnew((void *)&newvar,
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

static void		reset_env(t_ms_data *msd, t_list *env_backup, int empty_env)
{
	t_list	*lst;

	if (empty_env)
	{
		ft_lstdel(&msd->env, shvar_del);
		msd->env = env_backup;
		env_backup = NULL;
	}
	ft_lst_remove_if(&msd->env, NULL, is_local_env);
	ft_lst_remove_if(&env_backup, NULL, is_local_env);
	while (env_backup)
	{
		lst = env_backup;
		env_backup = env_backup->next;
		lst->next = NULL;
		ft_lst_sorted_insert(&msd->env, lst, shvar_cmp);
	}
}

static void		exec_with_tmp_env(char **argv, t_ms_data *msd, int empty_env)
{
	char	**path_backup;
	t_list	*env_backup;

	env_backup = NULL;
	path_backup = NULL;
	if (empty_env)
	{
		env_backup = msd->env;
		msd->env = NULL;
	}
	set_tmp_env(&argv, msd, &env_backup);
	if (get_shvar("PATH", env_backup))
	{
		path_backup = msd->path;
		msd->path = ft_strsplit(get_shvar_val("PATH", msd->env), ':');
	}
	if (*argv)
		ms_execution(msd, &argv, CMD_KEEP);
	reset_env(msd, env_backup, empty_env);
	if (path_backup || (!get_shvar_val("PATH", msd->env) && msd->path))
	{
		ft_wtfree(msd->path);
		msd->path = path_backup;
	}
}

int				msb_env(char **argv, t_ms_data *msd)
{
	t_optdata	od;
	int			argc;
	char		**env;
	int			empty_env;

	empty_env = 0;
	if ((argc = ft_wtlen(argv)) == 1)
	{
		if ((env = list_to_env(msd->env)))
		{
			ft_print_words_tables(env);
			ft_wtfree(env);
		}
	}
	else
	{
		init_getopt(&od, "i", 0, 0);
		while (ft_getopt(argc, argv, &od) != -1)
			empty_env = 1;
		argv += od.optind;
		if (*argv)
			exec_with_tmp_env(argv, msd, empty_env);
	}
	return (0);
}
