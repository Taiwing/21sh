/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:33:22 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 15:53:32 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "ms_data.h"

enum			e_tokenid {T_WORD, T_SEPARATOR};
enum			e_alias_mode {ALIAS_OFF, ALIAS_ON};

typedef struct	s_token
{
	int			id;
	char		*str;
}				t_token;

void			discard_token(t_list **alst);
void			del_token(void *content, size_t size);
void			add_token(t_list **lst, int id, char *str);
void			check_alias(t_ms_data *msd, t_list **lst, char *word);
t_list			*tokenize(t_ms_data *msd, char *input,
					int qmode, int alias);

#endif
