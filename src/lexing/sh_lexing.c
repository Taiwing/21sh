/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:02:54 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/16 14:19:14 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "quotes.h"
#include "t_shvar.h"
#include "sh_lexing.h"

t_list		*sh_lexing(t_sh_data *shd, char **input, int history)
{
	char	*nl;
	size_t	len;
	t_list	*lst;

	lst = NULL;
	*input = join_lines(*input, NO_QUOTE);
	if (history && *input && (len = ft_strlen(*input)) > 1
		&& len < CMDMAX && (!(nl = ft_strchr(*input, '\n')) || !nl[1]))
	{
		add_to_history(*input, &shd->hist, get_shvar_val("HOME", shd->env),
			&shd->cmd_c);
		++shd->cmd_c;
	}
	if (*input)
		lst = tokenize(shd, *input, NO_QUOTE);
	return (lst);
}
