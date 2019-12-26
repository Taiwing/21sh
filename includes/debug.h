/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:29:47 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/26 13:24:56 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "sh_parsing.h"

void				show_token(t_token *tok);						//TODO: delete
void				show_parse_tree(t_sh_data *shd, t_node *ptr, int lvl);	//TODO: delete
void				init_ppt(t_sh_data *shd);						//TODO: delete

extern char * const	g_token_id_str[TOKEN_COUNT + 2];
extern char * const	g_token_type_str[5];
extern char * const	g_prod_str[PRODS_COUNT];

#endif
