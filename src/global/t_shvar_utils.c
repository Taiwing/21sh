/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shvar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:47:15 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 12:54:09 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"

int		shvar_cmp(void *svar1, void *svar2)
{
	return (ft_strcmp(((t_shvar *)svar1)->name, ((t_shvar *)svar2)->name));
}

int		name_shvar_cmp(void *name, void *svar)
{
	if (!ft_strcmp((char *)name, ((t_shvar *)svar)->name))
	{
		shvar_del(svar, 0);
		return (0);
	}
	return (1);
}

void	shvar_del(void *content, size_t content_size)
{
	t_shvar	*svar;

	(void)content_size;
	svar = (t_shvar *)content;
	if (svar->name)
		free(ft_heap_collector((void *)svar->name, FT_COLLEC_GET));
	if (svar->value)
		free(ft_heap_collector((void *)svar->value, FT_COLLEC_GET));
	free(ft_heap_collector(content, FT_COLLEC_GET));
}
