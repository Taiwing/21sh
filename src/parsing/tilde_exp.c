/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:44:28 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/30 13:55:34 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_data.h"
#include "t_shvar.h"

void		tilde_exp(t_ms_data *msd, char **str)
{
	char	*dir;
	char	*slash;

	if (!*str || **str != '~' || ((*str)[1] && (*str)[1] != '/'))
		return ;
	slash = (*str)[1] == '/' ? *str + 1 : NULL;
	dir = get_shvar_val("HOME", msd->env);
	dir = ft_strdup(dir ? dir : "");
	dir = slash ? ft_stradd(&dir, slash, ft_strlen(slash)) : dir;
	if (!ft_strcmp(dir, ""))
		ft_memdel((void **)&dir);
	ft_memdel((void **)str);
	*str = dir;
}
