/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:11:28 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 16:00:42 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"
#include "libft.h"

int		get_qmode(int qmode, char c)
{
	if (c && (qmode & BSQUOTE))
		return (qmode & ~BSQUOTE);
	else if (c == '\\' && qmode != SQUOTE)
		return (qmode | BSQUOTE);
	else if (c == '"' && qmode != SQUOTE)
		return (qmode == DQUOTE ? NO_QUOTE : DQUOTE);
	else if (c == '\'' && qmode != DQUOTE)
		return (qmode == SQUOTE ? NO_QUOTE : SQUOTE);
	return (qmode);
}

char	*join_lines(char *str, int qmode)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n' && (qmode & BSQUOTE))
		{
			str = ft_strrm(&str, --i, 2);
			qmode &= ~BSQUOTE;
		}
		else
			qmode = get_qmode(qmode, str[i++]);
	}
	return (str);
}

char	*unquote_str(char *quoted_str)
{
	char	*cpy;
	int		i;
	int		qmode;
	int		old_qmode;

	if (!quoted_str || !(cpy = ft_strnew(ft_strlen(quoted_str))))
		return (NULL);
	i = 0;
	old_qmode = NO_QUOTE;
	while (*quoted_str)
	{
		qmode = get_qmode(old_qmode, *quoted_str);
		if (qmode == old_qmode || qmode == (old_qmode & ~BSQUOTE))
			cpy[i++] = *quoted_str;
		++quoted_str;
	}
	cpy[i] = 0;
	return (cpy);
}
