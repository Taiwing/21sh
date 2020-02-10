/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_ppt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:12:20 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/10 18:01:32 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_input.h"
#include "sh_lexing.h"
#include "sh_parsing.h"
#include "c_colors.h"
#include "debug.h"
#include <termcap.h>

#define MAX_LVL		1024
#define STR_FIELD 	19
#define MIDDLE		9

static int	loc_putchar(int c)
{
	return (write(0, &c, 1));
}

static void	init_curs_pos(t_sh_data *shd, int start_pos[2],
		int offset[MAX_LVL], int *max_offset)
{
	start_pos[X] = 0;
	start_pos[Y] = 0;
	ft_bzero(offset, MAX_LVL * sizeof(int));
	offset[0] = 1;
	*max_offset = 1;
	tputs(tgoto(shd->cm_cap, start_pos[X], start_pos[Y]), 1, loc_putchar);
	tputs(tgetstr("cl", NULL), 1, loc_putchar);
}

static void	set_curs_pos(t_sh_data *shd, int lvl)
{
	static int	offset[MAX_LVL] = {0};
	static int	start_pos[2] = {0};
	static int	max_offset = 0;
	int			base;

	if (!lvl)
		return (init_curs_pos(shd, start_pos, offset, &max_offset));
	base = offset[lvl] < offset[lvl - 1] ? offset[lvl - 1] : offset[lvl];
	offset[lvl] = max_offset > base ? max_offset + 1 : offset[lvl] + 1;
	offset[lvl] = offset[lvl] < base ? base : offset[lvl];
	tputs(tgoto(shd->cm_cap, start_pos[X] + (base - 1) * STR_FIELD
		+ MIDDLE, start_pos[Y] + (lvl - 1) * 2 + 1), 1, loc_putchar);
	ft_putstr_fd(C_GREEN"|", 0);
	while (base++ < offset[lvl])
		ft_dprintf(0, "------------------%c", base == offset[lvl] ? '|' : '-');
	ft_putstr_fd(C_RESET, 0);
	tputs(tgoto(shd->cm_cap, start_pos[X] + (offset[lvl] - 1) * STR_FIELD,
		start_pos[Y] + lvl * 2), 1, loc_putchar);
	max_offset = offset[lvl] > max_offset ? offset[lvl] : max_offset;
}

void		show_parse_tree(t_sh_data *shd, t_node *node, int lvl)
{
	int			len;
	char		*str;
	t_node		**ptr;
	static int	max_lvl = 0;

	if (!node || lvl == MAX_LVL)
		return ;
	max_lvl = lvl > max_lvl ? lvl : max_lvl;
	set_curs_pos(shd, lvl);
	if (node->id != P_TERM)
		str = g_prod_str[node->id];
	else if (node->t_id != I_WORD && node->t_id != I_IO_NUMBER)
		str = g_token_id_str[node->t_id];
	else
		str = node->str;
	len = ft_strlen(str);
	len = len > STR_FIELD ? STR_FIELD : len;
	ft_dprintf(0, "%*.*s", STR_FIELD - ((STR_FIELD - len) / 2),
		STR_FIELD, str);
	ptr = node->nodes;
	while (*ptr)
		show_parse_tree(shd, *ptr++, lvl + 1);
	if (!lvl)
		tputs(tgoto(shd->cm_cap, 0, max_lvl * 2 + 1), 1, loc_putchar);
}

int	shb_ppt(char **argv, t_sh_data *shd)
{
	char	*input;
	t_list	*tokens;
	t_node	*parse_tree;

	if (!shd->ppt || ft_wtlen(argv) != 2)
	{
		ft_putstr_fd(shd->ppt ? "ppt: wrong number of arguments\n"
			: SHELL_NAME": the 'ppt' builtin is disabled\n", 2);
		return (1);
	}
	parse_tree = NULL;
	input = ft_strdup(argv[1]);
	if ((tokens = sh_lexing(shd, &input)))
	{
		if (!expect_prod(P_COMPLETE_COMMAND, I_NONE, &tokens, &parse_tree))
			ft_printf(SHELL_NAME": parsing error\n");
		else
		{
			show_parse_tree(shd, parse_tree, 0);
			destroy_tree(parse_tree, 1);
		}
		destroy_token_list(&tokens);
	}
	ft_memdel((void **)&input);
	return (0);
}
