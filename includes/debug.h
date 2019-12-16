/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:29:47 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 21:53:57 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

#include "sh_parsing.h"

void				show_token(t_token *token);
void				show_parse_tree(t_node *parse_tree);

extern char * const	g_token_id_str[TOKEN_COUNT + 2];
extern char * const	g_token_type_str[5];
extern char * const	g_prod_str[PRODS_COUNT];

#endif
