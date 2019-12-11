/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:49:09 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/06 20:06:01 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dllst.h"
#include "libft.h"

t_dllst	*dllst_new(char c)
{
	t_dllst	*new;

	if ((new = (t_dllst *)ft_secmalloc(sizeof(t_dllst))))
	{
		new->prev = NULL;
		new->next = NULL;
		new->c = c;
	}
	return (new);
}

t_dllst	*dllst_insert_forwd(t_dllst **alst, char c)
{
	t_dllst	*new;

	if (!alst || !(new = dllst_new(c)))
		return (NULL);
	if (*alst)
	{
		new->next = (*alst)->next;
		if (new->next)
			new->next->prev = new;
		new->prev = (*alst);
		(*alst)->next = new;
	}
	*alst = new;
	return (new);
}

t_dllst	*dllst_insert_back(t_dllst **alst, char c)
{
	t_dllst	*new;

	if (!alst || !(new = dllst_new(c)))
		return (NULL);
	new->next = *alst;
	if (*alst)
		(*alst)->prev = new;
	new->prev = NULL;
	*alst = new;
	return (new);
}
