/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charfunc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:40:04 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:09:51 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charfunc.h"
#include "quotes.h"

void		reprint_line(t_dllst *lst)
{
	size_t	sz;

	sz = dllst_print(lst) + 1;
	write(0, " ", 1);
	while (sz--)
		write(0, g_multibyte_chars[LEFT_ARROW - 11], 3);
}

static int	get_word_qmode(int *word, int qmode, char *str)
{
	int	i;

	if (!str)
		return (NO_QUOTE);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!qmode && (!i || ft_strchr(" \t\n;", str[i])))
		{
			while (str[i] && ft_strchr(" \t\n;", str[i]))
			{
				*word = str[i] == ';' ? 0 : *word;
				++i;
			}
			if (str[i] && !(str[i] == '\\' && str[i + 1] == '\n'))
				++(*word);
		}
		if (str[i])
			qmode = get_qmode(qmode, str[i++]);
	}
	if ((qmode & ~BSQUOTE))
		qmode &= ~BSQUOTE;
	return (qmode);
}

void		check_input(t_input_data *idat, t_sh_data *shd)
{
	char	*recbuf;

	if ((idat->qmode = get_word_qmode(&idat->word, idat->qmode, idat->buf))
		!= NO_QUOTE)
	{
		if (!(recbuf = sh_input(shd, idat->qmode, idat->word)))
		{
			ft_memdel((void **)&idat->buf);
			dllst_del(dllst_first(idat->lst));
			idat->lst = NULL;
			return ;
		}
		idat->buf = ft_stradd(&idat->buf, recbuf, ft_strlen(recbuf));
		free(ft_heap_collector(recbuf, FT_COLLEC_GET));
	}
}
