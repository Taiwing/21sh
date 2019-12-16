/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:27:45 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 22:14:13 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parsing.h"
#include "c_colors.h"

char * const	g_token_id_str[TOKEN_COUNT + 2] = {
	"I_NEWLINE",
	"I_SEMI",
	"I_AND",
	"I_LESS",
	"I_GREAT",
	"I_PIPE",
	"I_AND_IF",
	"I_OR_IF",
	"I_DLESS",
	"I_DGREAT",
	"I_LESSAND",
	"I_GREATAND",
	"I_LESSGREAT",
	"I_CLOBBER",
	"I_DLESSDASH",
	"I_IO_NUMBER",
	"I_WORD",
	"I_NONE",
	NULL
};

char * const	g_token_type_str[5] = {
	"T_SEPERATOR",
	"T_OPERATOR",
	"T_OTHER",
	"T_NONE",
	NULL
};

void			show_token(t_token *token)
{
	char	*new_line;

	ft_printf("[ type = %s, id = %s, ", g_token_type_str[token->type],
		g_token_id_str[token->id]);
	if (!(new_line = ft_strchr(token->str, '\n'))
		|| (int)(new_line - token->str) >= token->len)
		ft_printf("len = %d, str = %.*s ]\n", token->len,
			token->len, token->str);
	else
	{
		ft_printf("len = %d, str = ", token->len);
		ft_printf("%.*s{\\n}", (int)(new_line - token->str), token->str);
		ft_printf("%.*s ]\n", token->len - (int)(new_line - token->str),
			new_line + 1);
	}
}

char * const g_prod_str[PRODS_COUNT] = {
	"P_COMPLETE_COMMAND",
	"P_LIST",
	"P_LIST_P",
	"P_AND_OR",
	"P_AND_OR_P",
	"P_PIPELINE",
	"P_PIPELINE_P",
	"P_COMMAND",
	"P_CMD_NAME",
	"P_CMD_WORD",
	"P_CMD_PREFIX",
	"P_CMD_SUFFIX",
	"P_IO_REDIRECT",
	"P_IO_FILE",
	"P_FILENAME",
	"P_IO_HERE",
	"P_HERE_END",
	"P_NEWLINE_LIST",
	"P_LINEBREAK",
	"P_SEPARATOR",
	"P_TERM"
};

void	show_parse_tree(t_node *parse_tree)
{
	t_node	**ptr;

	if (!parse_tree)
		return ;
	ft_printf("[ prod = %s, t_id = %s, str = %s ]",
		g_prod_str[parse_tree->id], g_token_id_str[parse_tree->t_id],
		parse_tree->str);
	ptr = parse_tree->nodes;
	ft_putstr(*ptr ? " -> " : "\n");
	while (*ptr)
	{
		ft_printf(C_GREEN"%s"C_RESET"%s", g_prod_str[(*ptr)->id],
			ptr[1] ? ", " : "\n");
		++ptr;
	}
	ptr = parse_tree->nodes;
	while (*ptr)
		show_parse_tree(*ptr++);
}
