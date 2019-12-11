/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:30:45 by yforeau           #+#    #+#             */
/*   Updated: 2019/05/03 22:25:03 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "ms_data.h"
#include "t_shvar.h"
#include "ms_signals.h"
#include "terminal_size.h"

void		set_custom_input_mode(void)
{
	struct termios			new_tattr;

	if (tcgetattr(0, &new_tattr) == -1)
		ft_exit("failed to get terminal attributes", EXIT_FAILURE);
	new_tattr.c_lflag &= ~(ICANON | ECHO | ISIG);
	new_tattr.c_cc[VMIN] = 1;
	new_tattr.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, &new_tattr) == -1)
		ft_exit("failed to set terminal attributes", EXIT_FAILURE);
}

void		reset_input_mode(void)
{
	static struct termios	*old_tattr = NULL;

	if (!old_tattr)
	{
		old_tattr = (struct termios *)ft_secmalloc(sizeof(struct termios));
		if (tcgetattr(0, old_tattr) == -1)
			ft_exit("failed to get terminal attributes", EXIT_FAILURE);
		set_custom_input_mode();
	}
	else
		tcsetattr(0, TCSANOW, old_tattr);
}

static void	set_needed_env(t_ms_data *msd)
{
	char	name[1024];
	char	*shlvl;

	if (!get_shvar("HOST", msd->env) && !gethostname(name, 1024))
		set_shvar("HOST", name, &msd->env, ENV_VAR);
	if (!get_shvar("PWD", msd->env) && getcwd(name, 1024))
		set_shvar("PWD", name, &msd->env, ENV_VAR);
	if (!get_shvar("USER", msd->env))
		set_shvar("USER", "john_doe", &msd->env, ENV_VAR);
	if (!(shlvl = get_shvar_val("SHLVL", msd->env)))
		set_shvar("SHLVL", "1", &msd->env, ENV_VAR);
	else
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		set_shvar("SHLVL", shlvl, &msd->env, ENV_VAR);
		ft_memdel((void **)&shlvl);
	}
}

void		ms_init(t_ms_data *msd, char **env)
{
	init_signals();
	ft_exitmsg("minishell");
	ft_dir_container();
	ft_atexit(ft_close_dir_stack);
	if (!isatty(0))
		ft_exit("not a terminal", EXIT_FAILURE);
	reset_input_mode();
	ft_atexit(reset_input_mode);
	msd->alias = NULL;
	msd->env = env_to_list(env);
	set_needed_env(msd);
	msd->path = ft_strsplit(get_shvar_val("PATH", msd->env), ':');
	msd->cmd_exit = 0;
	msd->process_id = 0;
	load_history(&msd->hist, get_shvar_val("HOME", msd->env));
	msd->cmd_c = 0;
	msd->term_width = get_terminal_width();
	term_width_container(&msd->term_width);
}
