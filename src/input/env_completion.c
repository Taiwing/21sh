/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 18:28:04 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/20 20:31:07 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tab_completion.h"
#include "t_shvar.h"

char	*env_completion(char *part, t_list *env)
{
	size_t	len;
	char	*comp;
	char	*name;

	comp = NULL;
	len = ft_strlen(part);
	while (env && (!comp || *comp))
	{
		name = ((t_shvar *)env->content)->name;
		comp = part_match(comp, name, part, len);
		env = env->next;
	}
	return (comp);
}
