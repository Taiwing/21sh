/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 18:29:46 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/20 20:26:39 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "tab_completion.h"

static char	*get_path(char **path, char *part)
{
	char	*sl;
	char	*ptr;

	sl = *part == '/' ? part : NULL;
	ptr = part;
	while ((ptr = ft_strchr(ptr + 1, '/')))
		sl = ptr;
	if (!sl)
		*path = ft_strdup(".");
	else
	{
		*path = ft_strsub(part, 0, (sl - part) + 1);
		part = sl + 1;
	}
	return (part);
}

static void	check_dir(char *path, char *part, char **comp)
{
	struct stat	st;
	char		*stpath;

	stpath = NULL;
	if (!*part || !*comp)
		return ;
	if (!ft_strcmp(path, "."))
		stpath = ft_strjoin(part, *comp);
	else
	{
		stpath = ft_strjoin(path, part);
		stpath = ft_stradd(&stpath, *comp, ft_strlen(*comp));
	}
	if (!stat(stpath, &st) && ((st.st_mode & S_IFMT) == S_IFDIR))
		*comp = ft_stradd(comp, "/", 1);
	ft_memdel((void **)&stpath);
}

char		*file_completion(char *part)
{
	size_t	len;
	char	*comp;
	char	*name;
	char	*path;
	t_list	*files;

	comp = NULL;
	part = get_path(&path, part);
	len = ft_strlen(part);
	if (*part && *part != '/')
	{
		files = ft_ls_files(path, FT_LS_ALL);
		while (files)
		{
			if (!comp || *comp)
			{
				name = (char *)(files->content);
				comp = part_match(comp, name, part, len);
			}
			ft_lst_discard(NULL, &files);
		}
	}
	check_dir(path, part, &comp);
	ft_memdel((void **)&path);
	return (comp);
}
