/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:18:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 01:23:35 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
** Tokens are ordered from smallest to biggest, with the variable tokens
** at the end (T_IO_NUMBER and T_WORD). This is the easiest way to check
** them all.
*/

char * const	g_token_str[TOKEN_COUNT + 1] = {
	"\n",
	";",
	"&",
	"<",
	">",
	"|",
	"&&",
	"||",
	"<<",
	">>",
	"<&",
	">&",
	"<>",
	">|",
	"<<-",
	NULL,
	NULL,
	NULL
};

void		discard_token(t_list **alst)
{
	t_list	*next;

	next = (*alst)->next;
	del_token((*alst)->content, 0);
	free(ft_heap_collector(*alst, FT_COLLEC_GET));
	*alst = next;
}

void		del_token(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
}

int			is_num_string(char *str, int len)
{
	while (len && *str && ft_isdigit(*str++))
		--len;
	return (!len);
}

enum e_tokentype	get_token_str_type(char *str, int len,
						enum e_tokenid *tok_id, int exact_match)
{
	int	id;

	id = -1;
	while (g_token_str[++id] && (ft_strncmp(g_token_str[id], str, len)
		|| (exact_match && g_token_str[id][len])))
		;
	if (tok_id)
		*tok_id = id;
	if (id == I_IO_NUMBER)
		return (T_OTHER);
	else if (id == I_NEWLINE || id == I_SEMI || (id == I_AND && exact_match))
		return (T_SEPARATOR);
	else
		return (T_OPERATOR);
}
