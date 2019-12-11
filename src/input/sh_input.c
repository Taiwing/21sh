/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:42:19 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:10:53 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charfunc.h"
#include "quotes.h"
#include "t_shvar.h"
#include "c_colors.h"
#include "terminal_size.h"
#include "terminal_cursor.h"

const char	*g_inputstr[5] = {
	"$",
	"dquote",
	"squote",
	NULL,
	""
};

static char	*get_current_dir(t_sh_data *shd, char *cwd)
{
	char	*home;
	char	*sl;

	home = get_shvar_val("HOME", shd->env);
	if (home && !ft_strcmp(home, cwd))
		cwd = "~";
	else
	{
		while ((sl = ft_strchr(cwd, '/')) && sl[1] && sl[1] != '/')
			cwd = sl + 1;
	}
	return (cwd);
}

static int	user_host_prompt(t_sh_data *shd)
{
	char	*user;
	char	*host;
	char	*cwd;

	if (!(user = get_shvar_val("USER", shd->env))
		|| !(host = get_shvar_val("HOST", shd->env))
		|| !(cwd = get_shvar_val("PWD", shd->env)))
		return (1);
	cwd = get_current_dir(shd, cwd);
	ft_dprintf(0, C_BOLD C_BLUE "%s@%s:" C_NO_BOLD, user, host);
	ft_dprintf(0, C_BOLD C_CYAN "%s" C_BLUE "%s> " C_NO_BOLD C_RESET,
		cwd, g_inputstr[NO_QUOTE]);
	return (0);
}

static void	print_prompt(t_sh_data *shd, int qmode)
{
	if (!qmode)
	{
		if (user_host_prompt(shd))
			ft_dprintf(0, C_BOLD C_BLUE "%s> " C_NO_BOLD C_RESET,
				g_inputstr[qmode]);
	}
	else
		ft_dprintf(0, "%s> ", g_inputstr[qmode]);
}

static int	sh_getchar(char c[8])
{
	int	i;
	int	rd;

	if ((rd = read(0, c, 8)) == -1)
		ft_exit("read_error", EXIT_FAILURE);
	if (rd == 1 && (c[0] > 31 || ft_strchr(INPUT_CONTROL_CHARS, c[0])))
		return (c[0]);
	else if (rd > 1)
	{
		i = -1;
		while (g_multibyte_chars[++i])
		{
			if (!ft_strcmp(g_multibyte_chars[i], c))
				return (i + 11);
		}
	}
	return (0);
}

char		*sh_input(t_sh_data *shd, int qmode, int word)
{
	t_input_data	idat;

	print_prompt(shd, qmode);
	idat.hi = 0;
	idat.bol = 1;
	idat.lst = NULL;
	idat.buf = NULL;
	idat.word = word;
	ft_bzero(idat.c, 8);
	get_curs_pos(idat.cursor_pos);
	curs_pos_container(idat.cursor_pos);
	shd->term_width = get_terminal_width();
	idat.qmode = qmode == BSQUOTE ? NO_QUOTE : qmode;
	while (g_charfunc[sh_getchar(idat.c)](&idat, shd))
		ft_bzero(idat.c, 8);
	return (idat.buf);
}
