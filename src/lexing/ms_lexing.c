/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:02:54 by yforeau           #+#    #+#             */
/*   Updated: 2019/05/04 20:05:51 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "quotes.h"
#include "t_shvar.h"
#include "ms_lexing.h"

t_list		*ms_lexing(t_ms_data *msd, char **input)
{
	char	*nl;
	size_t	len;
	t_list	*lst;

	lst = NULL;
	*input = join_lines(*input, NO_QUOTE);
	if (*input && (len = ft_strlen(*input)) > 1 && len < CMDMAX
		&& (!(nl = ft_strchr(*input, '\n')) || !nl[1]))
	{
		add_to_history(*input, &msd->hist, get_shvar_val("HOME", msd->env),
			&msd->cmd_c);
		++msd->cmd_c;
	}
	if (*input)
	{
		lst = tokenize(msd, *input, NO_QUOTE, ALIAS_ON);
		ft_memdel((void **)input);
	}
	return (lst);
}
