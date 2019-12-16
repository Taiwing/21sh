/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_functions_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:12:13 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 22:40:40 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parsing.h"

int	p_pipeline(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!expect_prod(P_COMMAND, I_NONE, token, &node))
		return (0);
	accept_prod(P_PIPELINE_P, I_NONE, token, &node);
	return (1);
}

int	p_pipeline_p(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!expect_prod(P_TERM, I_PIPE, token, &node))
		return (0);
	accept_prod(P_LINEBREAK, I_NONE, token, &node);
	return (expect_prod(P_PIPELINE, I_NONE, token, &node));
}

int	p_command(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	accept_prod(P_CMD_PREFIX, I_NONE, token, &node);
	if (!expect_prod(P_CMD_NAME, I_NONE, token, &node))
		return (0);
	accept_prod(P_CMD_SUFFIX, I_NONE, token, &node);
	return (1);
}

int	p_cmd_name(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	return (expect_prod(P_TERM, I_WORD, token, &node));
}

int	p_cmd_word(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	return (expect_prod(P_TERM, I_WORD, token, &node));
}
