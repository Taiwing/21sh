/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 18:32:29 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/20 18:42:44 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	reduce_match(char *comp, char *name)
{
	while (*comp && *name && *comp == *name)
	{
		++comp;
		++name;
	}
	*comp = 0;
}

char	*part_match(char *comp, char *name, char *part, size_t len)
{
	if (!ft_strncmp(part, name, len))
	{
		if (!comp)
			comp = ft_strdup(name + len);
		else
			reduce_match(comp, name + len);
	}
	return (comp);
}
