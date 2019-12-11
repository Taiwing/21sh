/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 13:38:12 by yforeau           #+#    #+#             */
/*   Updated: 2019/05/02 23:56:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tab_completion.h"
#include "charfunc.h"
#include "quotes.h"
#include "terminal_cursor.h"

static int	get_dllst_word_qmode(int *word, int qmode, t_dllst *lst)
{
	t_dllst	*ptr;

	ptr = dllst_first(lst);
	while (ptr != lst->next)
	{
		if (!qmode && (!ptr->prev || ft_strchr(" \t\n;", ptr->c)))
		{
			while (ptr != lst->next && ft_strchr(" \t\n;", ptr->c))
			{
				*word = ptr->c == ';' ? 0 : *word;
				ptr = ptr->next;
			}
			if (ptr != lst->next)
				++(*word);
		}
		if (ptr != lst->next)
		{
			qmode = get_qmode(qmode, ptr->c);
			ptr = ptr->next;
		}
	}
	return (qmode);
}

int			check_completion(t_input_data *idat, char **part)
{
	int		word;
	int		qmode;
	size_t	size;
	t_dllst	*beg;

	word = idat->word;
	if (idat->bol || ft_strchr(" \t\n", idat->lst->c)
		|| (idat->lst->next && !ft_strchr(" \t\n;", idat->lst->next->c))
		|| (qmode = get_dllst_word_qmode(&word, idat->qmode, idat->lst))
		|| !word)
		return (NO_COMP);
	size = 1;
	beg = idat->lst;
	while (beg->prev && !ft_strchr(" \t\n;$", beg->prev->c))
	{
		beg = beg->prev;
		++size;
	}
	*part = dllst_to_nstr(beg, size);
	if (beg->prev && beg->prev->c == '$')
		return (ENV_COMP);
	else if (word == 1 && !ft_strchr(*part, '/'))
		return (EXEC_COMP);
	else
		return (FILE_COMP);
}

static void	insert_comp(char *comp, t_input_data *idat)
{
	while (*comp)
	{
		write(0, comp, 1);
		dllst_insert_forwd(&idat->lst, *comp);
		++comp;
	}
	if (idat->lst->next)
		reprint_line(idat->lst->next);
	get_curs_pos(idat->cursor_pos);
}

void		complete_input(int completion, char *part,
				t_input_data *idat, t_ms_data *msd)
{
	char	*comp;

	comp = NULL;
	if (completion == ENV_COMP)
		comp = env_completion(part, msd->env);
	else if (completion == EXEC_COMP)
		comp = exec_completion(part, msd->path);
	else if (completion == FILE_COMP)
		comp = file_completion(part);
	ft_memdel((void **)&part);
	if (comp && *comp)
		insert_comp(comp, idat);
	ft_memdel((void **)&comp);
}
