/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_functions_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:13:17 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 22:40:51 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parsing.h"

int	p_io_here(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!accept_prod(P_TERM, I_DLESS, token, &node)
		&& !expect_prod(P_TERM, I_DLESSDASH, token, &node))
		return (0);
	return (expect_prod(P_HERE_END, I_NONE, token, &node));
}

int	p_here_end(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	return (expect_prod(P_TERM, I_WORD, token, &node));
}

int	p_newline_list(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!expect_prod(P_TERM, I_NEWLINE, token, &node))
		return (0);
	while (accept_prod(P_TERM, I_NEWLINE, token, &node))
		;
	return (1);
}

int	p_linebreak(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	return (expect_prod(P_NEWLINE_LIST, I_NONE, token, &node));
}

int	p_separator(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (accept_prod(P_TERM, I_SEMI, token, &node)
		|| accept_prod(P_TERM, I_SEMI, token, &node))
	{
		accept_prod(P_LINEBREAK, I_NONE, token, &node);
		return (1);
	}
	return (expect_prod(P_NEWLINE_LIST, I_NONE, token, &node));
}
