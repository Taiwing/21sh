/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_functions_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:13:24 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 22:40:45 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parsing.h"

int	p_cmd_prefix(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!expect_prod(P_IO_REDIRECT, I_NONE, token, &node))
		return (0);
	accept_prod(P_CMD_PREFIX, I_NONE, token, &node);
	return (1);
}

int	p_cmd_suffix(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!accept_prod(P_IO_REDIRECT, I_NONE, token, &node)
		&& !expect_prod(P_CMD_WORD, I_NONE, token, &node))
		return (0);
	accept_prod(P_CMD_SUFFIX, I_NONE, token, &node);
	return (1);
}

int	p_io_redirect(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	accept_prod(P_TERM, I_IO_NUMBER, token, &node);
	if (!accept_prod(P_IO_FILE, I_NONE, token, &node)
		&& !expect_prod(P_IO_HERE, I_NONE, token, &node))
		return (0);
	return (1);
}

int	p_io_file(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	if (!accept_prod(P_TERM, I_LESS, token, &node)
		&& !accept_prod(P_TERM, I_LESSAND, token, &node)
		&& !accept_prod(P_TERM, I_GREAT, token, &node)
		&& !accept_prod(P_TERM, I_GREATAND, token, &node)
		&& !accept_prod(P_TERM, I_DGREAT, token, &node)
		&& !accept_prod(P_TERM, I_LESSGREAT, token, &node)
		&& !expect_prod(P_TERM, I_CLOBBER, token, &node))
		return (0);
	return (expect_prod(P_FILENAME, I_NONE, token, &node));
}

int	p_filename(enum e_tokenid t_id, t_list **token, t_node *node)
{
	(void)t_id;
	return (expect_prod(P_TERM, I_WORD, token, &node));
}
