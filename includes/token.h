/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:33:22 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 01:13:44 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "sh_data.h"

# define TOKEN_COUNT 17

/*
** T_SEPARATOR:	I_NEWLINE, I_SEMI, I_AND ('&' is the same as ';' for now)
** T_OPERATOR:	I_LESS, I_GREAT, I_PIPE, I_AND_IF, I_OR_IF, I_DLESS, I_DGREAT,
**				I_LESSAND, I_GREATAND, I_LESSGREAT, I_CLOBBER, I_DLESSDASH,
** T_OTHER:		I_IO_NUMBER, I_WORD
*/

enum			e_tokenid {I_NEWLINE, I_SEMI, I_AND, I_LESS, I_GREAT, I_PIPE,
					I_AND_IF, I_OR_IF, I_DLESS, I_DGREAT, I_LESSAND,
					I_GREATAND, I_LESSGREAT, I_CLOBBER, I_DLESSDASH, 
					I_IO_NUMBER, I_WORD, I_NONE};

enum			e_tokentype {T_SEPARATOR, T_OPERATOR, T_OTHER, T_NONE};

extern char	* const	g_token_str[TOKEN_COUNT + 1];

typedef struct			s_token
{
	enum e_tokenid		id;
	enum e_tokentype	type;
	int					len;
	char				*str;
}						t_token;

void					discard_token(t_list **alst);
void					del_token(void *content, size_t size);
int						is_num_string(char *str, int len);
enum e_tokentype		get_token_str_type(char *str, int len,
							enum e_tokenid *tok_id, int exact_match);
t_list					*tokenize(t_sh_data *shd, char *input, int qmode);

#endif
