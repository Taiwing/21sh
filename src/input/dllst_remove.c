/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:03:57 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 17:04:49 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dllst.h"
#include "libft.h"

void	dllst_remove_back(t_dllst **alst)
{
	t_dllst	*prev;
	t_dllst	*next;

	if (!alst || !*alst)
		return ;
	prev = (*alst)->prev;
	next = (*alst)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(ft_heap_collector(*alst, FT_COLLEC_GET));
	*alst = prev ? prev : next;
}

void	dllst_remove_forwd(t_dllst **alst)
{
	t_dllst	*next;

	if (!alst || !*alst || !(*alst)->next)
		return ;
	next = (*alst)->next;
	dllst_remove_back(&next);
}

void	dllst_del(t_dllst *lst)
{
	if (!lst)
		return ;
	dllst_del(lst->next);
	free(ft_heap_collector(lst, FT_COLLEC_GET));
}
