/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:29:41 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/15 17:46:22 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "quotes.h"
#include "t_shvar.h"

static void	delimit_token(t_list **lst, t_token *token)
{
	if (token->len)
	{
		if (token->type == T_OTHER && is_num_string(token->str, token->len)
			&& ft_strchr("<>", token->str[token->len]))
			token->id = I_IO_NUMBER;
		else if (token->type == T_OTHER)
			token->id = I_WORD;
		else
			token->type = get_token_str_type(token->str,
				token->len, &token->id, 1);
		ft_lst_push_back(lst, (void *)token, sizeof(t_token));
	}
	token->id = I_NONE;
	token->type = T_NONE;
	token->len = 0;
	token->str = NULL;
}

static void	add_char(char *c, t_token *token, int *qmode, t_list **lst)
{
	enum e_tokentype	new_type;

	new_type = T_NONE;
	if (!*c)
		delimit_token(lst, token);
	else if (token->type == T_OPERATOR && token->type
		== get_token_str_type(token->str, token->len + 1, NULL, 0))
		++token->len;
	else
	{
		new_type = get_token_str_type(c, 1, NULL, 0);
		if (token->type == T_OPERATOR || (!*qmode &&
			(new_type != T_OTHER || ft_strchr(" \t", *c))))
			delimit_token(lst, token);
		else if (token->type == T_OTHER)
			++token->len;
	}
	if (token->type == T_NONE && !ft_strchr(" \t", *c))
	{
		token->type = new_type;
		token->len = 1;
		token->str = c;
	}
	*qmode = get_qmode(*qmode, *c);
}

t_list		*tokenize(t_sh_data *shd, char *input, int qmode)
{
	int			i;
	t_list		*lst;
	t_token		token;

	(void)shd;
	i = -1;
	lst = NULL;
	token.len = 0;
	delimit_token(&lst, &token);
	while (input[++i])
		add_char(input + i, &token, &qmode, &lst);
	add_char(input + i, &token, &qmode, &lst);
	return (lst);
}
