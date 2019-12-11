/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:24:44 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 12:52:18 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"

t_shvar	*get_shvar(char *name, t_list *lst)
{
	t_shvar	sv;
	t_list	*ptr;

	sv.name = name;
	if (!(ptr = ft_lst_find(lst, (void *)&sv, shvar_cmp)))
		return (NULL);
	return ((t_shvar *)ptr->content);
}

char	*get_shvar_val(char *name, t_list *lst)
{
	t_shvar	*ptr;

	if (!(ptr = get_shvar(name, lst)))
		return (NULL);
	else
		return (ptr->value);
}

void	set_shvar(const char *name, const char *value, t_list **lst, int type)
{
	t_shvar	*ptr;
	t_shvar	svar;

	if (!(ptr = get_shvar((char *)name, *lst)))
	{
		svar.name = ft_strdup((char *)name);
		svar.value = value ? ft_strdup((char *)value) : NULL;
		svar.type = type;
		ft_lst_sorted_insert(lst, ft_lstnew((void *)&svar, sizeof(t_shvar)),
			shvar_cmp);
	}
	else
	{
		ft_memdel((void **)&ptr->value);
		ptr->value = value ? ft_strdup((char *)value) : NULL;
	}
}
