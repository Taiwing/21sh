/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shb_ptok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:14:48 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/20 18:39:01 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexing.h"
#include "debug.h"
#include "token.h"

void	show_token(t_token *token)
{
	char	*new_line;

	ft_printf("[ type = %s, id = %s, ", g_token_type_str[token->type],
		g_token_id_str[token->id]);
	if (!(new_line = ft_strchr(token->str, '\n'))
		|| (int)(new_line - token->str) >= token->len)
		ft_printf("len = %d, str = %.*s ]\n", token->len,
			token->len, token->str);
	else
	{
		ft_printf("len = %d, str = ", token->len);
		ft_printf("%.*s{\\n}", (int)(new_line - token->str), token->str);
		ft_printf("%.*s ]\n", token->len - (int)(new_line - token->str),
			new_line + 1);
	}
}

int		shb_ptok(char **argv, t_sh_data *shd)
{
	char	*input;
	t_list	*tokens;

	if (ft_wtlen(argv) != 2)
	{
		ft_putstr_fd("ptok: wrong number of arguments\n", 2);
		return (1);
	}
	input = ft_strdup(argv[1]);
	if ((tokens = sh_lexing(shd, &input)))
	{
		while (tokens)
		{
			show_token(tokens->content);
			discard_token(&tokens);
		}
	}
	ft_memdel((void **)&input);
	return (0);
}
