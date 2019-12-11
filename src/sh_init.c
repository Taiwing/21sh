/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:30:45 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:18:55 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "sh_data.h"
#include "t_shvar.h"
#include "sh_signals.h"
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

static void	set_needed_env(t_sh_data *shd)
{
	char	name[1024];
	char	*shlvl;

	if (!get_shvar("HOST", shd->env) && !gethostname(name, 1024))
		set_shvar("HOST", name, &shd->env, ENV_VAR);
	if (!get_shvar("PWD", shd->env) && getcwd(name, 1024))
		set_shvar("PWD", name, &shd->env, ENV_VAR);
	if (!get_shvar("USER", shd->env))
		set_shvar("USER", "john_doe", &shd->env, ENV_VAR);
	if (!(shlvl = get_shvar_val("SHLVL", shd->env)))
		set_shvar("SHLVL", "1", &shd->env, ENV_VAR);
	else
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		set_shvar("SHLVL", shlvl, &shd->env, ENV_VAR);
		ft_memdel((void **)&shlvl);
	}
}

void		sh_init(t_sh_data *shd, char **env)
{
	init_signals();
	ft_exitmsg(SHELL_NAME);
	ft_dir_container();
	ft_atexit(ft_close_dir_stack);
	if (!isatty(0))
		ft_exit("not a terminal", EXIT_FAILURE);
	reset_input_mode();
	ft_atexit(reset_input_mode);
	shd->alias = NULL;
	shd->env = env_to_list(env);
	set_needed_env(shd);
	shd->path = ft_strsplit(get_shvar_val("PATH", shd->env), ':');
	shd->cmd_exit = 0;
	shd->process_id = 0;
	load_history(&shd->hist, get_shvar_val("HOME", shd->env));
	shd->cmd_c = 0;
	shd->term_width = get_terminal_width();
	term_width_container(&shd->term_width);
}
