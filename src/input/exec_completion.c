/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 18:29:08 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/20 18:54:57 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tab_completion.h"
#include "g_builtins.h"

static char	*builtin_comp(char *part)
{
	int		i;
	size_t	len;
	char	*comp;
	char	*name;

	i = 0;
	comp = NULL;
	len = ft_strlen(part);
	while (i < BUILTIN_COUNT && (!comp || *comp))
	{
		name = g_builtins[i].name;
		comp = part_match(comp, name, part, len);
		++i;
	}
	return (comp);
}

char		*exec_completion(char *part, char **path)
{
	size_t	len;
	char	*comp;
	char	*name;
	t_list	*files;

	comp = builtin_comp(part);
	len = ft_strlen(part);
	while (path && *path && (!comp || *comp))
	{
		files = ft_ls_files(*path, FT_LS_REG | FT_LS_LNK);
		while (files)
		{
			if (!comp || *comp)
			{
				name = (char *)(files->content);
				comp = part_match(comp, name, part, len);
			}
			ft_lst_discard(NULL, &files);
		}
		++path;
	}
	return (comp);
}
