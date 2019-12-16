/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_functions_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:10:16 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 22:40:34 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parsing.h"

int	p_complete_command(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!expect_prod(P_LIST, I_NONE, token, &node))
		return (0);
	accept_prod(P_SEPARATOR, I_NONE, token, &node);
	return (!*token);
}

int	p_list(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!expect_prod(P_AND_OR, I_NONE, token, &node))
		return (0);
	accept_prod(P_LIST_P, I_NONE, token, &node);
	return (1);
}

int	p_list_p(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!accept_prod(P_TERM, I_SEMI, token, &node)
		&& !expect_prod(P_TERM, I_AND, token, &node))
		return (0);
	return (expect_prod(P_LIST, I_NONE, token, &node));
}

int	p_and_or(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!expect_prod(P_PIPELINE, I_NONE, token, &node))
		return (0);
	accept_prod(P_AND_OR_P, I_NONE, token, &node);
	return (1);
}

int	p_and_or_p(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!accept_prod(P_TERM, I_AND_IF, token, &node)
		&& !expect_prod(P_TERM, I_OR_IF, token, &node))
		return (0);
	accept_prod(P_LINEBREAK, I_NONE, token, &node);
	return (expect_prod(P_AND_OR, I_NONE, token, &node));
}
