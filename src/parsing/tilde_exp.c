/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:44:28 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:14:48 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_data.h"
#include "t_shvar.h"

void		tilde_exp(t_sh_data *shd, char **str)
{
	char	*dir;
	char	*slash;

	if (!*str || **str != '~' || ((*str)[1] && (*str)[1] != '/'))
		return ;
	slash = (*str)[1] == '/' ? *str + 1 : NULL;
	dir = get_shvar_val("HOME", shd->env);
	dir = ft_strdup(dir ? dir : "");
	dir = slash ? ft_stradd(&dir, slash, ft_strlen(slash)) : dir;
	if (!ft_strcmp(dir, ""))
		ft_memdel((void **)&dir);
	ft_memdel((void **)str);
	*str = dir;
}
