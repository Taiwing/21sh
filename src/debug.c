/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:27:45 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 01:47:07 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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
