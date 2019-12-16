/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:31:22 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/15 21:20:09 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "tilde_exp.h"
#include "param_exp.h"
#include "quotes.h"

static void	rm_quotes(char **str)
{
	char	*dup;
	char	*pdup;
	char	*pstr;
	int		qmode;
	int		old_qmode;

	if (!*str)
		return ;
	pstr = *str;
	dup = NULL;
	old_qmode = NO_QUOTE;
	while (*pstr)
	{
		if ((qmode = get_qmode(old_qmode, *pstr)) != old_qmode && !dup)
		{
			dup = ft_strncat(ft_strnew(ft_strlen(*str)), *str, pstr - *str);
			pdup = dup + (pstr - *str);
		}
		else if ((qmode == old_qmode || qmode == (old_qmode & ~BSQUOTE)) && dup)
			*pdup++ = *pstr;
		old_qmode = qmode;
		++pstr;
	}
	*str = dup ? ft_strcpy(*str, dup) : *str;
	ft_memdel((void **)&dup);
}

static int	expand(t_sh_data *shd, t_list *cmd_list)
{
	t_token	*tok;
	int		argc;

	(void)shd;
	argc = 0;
//	while (cmd_list && (tok = (t_token *)cmd_list->content)->id == T_WORD)
	while (cmd_list && (tok = (t_token *)cmd_list->content)->id == I_WORD) //TEMP
	{
		tilde_exp(shd, &tok->str);
		param_exp(shd, &tok->str);
		rm_quotes(&tok->str);
		cmd_list = cmd_list->next;
		argc = tok->str ? argc + 1 : argc;
	}
	return (argc);
}

char		**sh_parsing(t_sh_data *shd, t_list **cmd_list)
{
	t_token	*tok;
	int		argc;
	char	**argv;

	argc = expand(shd, *cmd_list);
	argv = argc ? ft_secmalloc((argc + 1) * sizeof(char *)) : NULL;
	argc = 0;
	while (*cmd_list
//			&& (tok = (t_token *)(*cmd_list)->content)->id == T_WORD)
			&& (tok = (t_token *)(*cmd_list)->content)->id == I_WORD) //TEMP
	{
		if (tok->str)
			argv[argc++] = tok->str;
		tok->str = NULL;
		discard_token(cmd_list);
	}
	if (argc)
		argv[argc] = NULL;
	while (*cmd_list
//		&& (tok = (t_token *)(*cmd_list)->content)->id == T_SEPARATOR)
		&& (tok = (t_token *)(*cmd_list)->content)->type == T_SEPARATOR) //TEMP
		discard_token(cmd_list);
	return (argv);
}
