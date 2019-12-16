/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_functions_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:13:05 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 22:42:47 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parsing.h"

int	p_term(enum e_tokenid t_id, t_list **token_ptr, t_node *node)
{
	t_token	*token;

	if (!*token_ptr)
		return (0);
	token = (t_token *)(*token_ptr)->content;
	if (token->id != t_id)
		return (0);
	node->t_id = t_id;
	if (token->type == T_OTHER)
		node->str = ft_strndup(token->str, token->len);
	*token_ptr = (*token_ptr)->next;
	return (1);
}
