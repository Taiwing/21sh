/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:45:56 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:14:25 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_data.h"
#include "quotes.h"
#include "t_shvar.h"

static int	get_name(char *str, int qmode)
{
	int	len;
	int	old_qmode;

	len = 0;
	old_qmode = qmode;
	if (str[len] && ft_strchr("$?", str[len]))
		return (1);
	while (str[len] && old_qmode == (qmode = get_qmode(qmode, str[len]))
			&& !ft_strchr(" \t\n$/", str[len]))
		++len;
	return (len);
}

static void	insert_value_string(char **str, size_t st,
								int name_len, char *val)
{
	char	*fp;
	char	*sp;
	char	*res;

	fp = ft_strsub(*str, 0, st);
	sp = ft_strdup(*str + st + name_len + 1);
	res = ft_strnew(ft_strlen(fp) + ft_strlen(sp)
		+ (val ? ft_strlen(val) : 0));
	ft_strcat(res, fp);
	if (val)
		ft_strcat(res, val);
	ft_strcat(res, sp);
	ft_memdel((void **)&fp);
	ft_memdel((void **)&sp);
	ft_memdel((void **)str);
	*str = res;
}

static char	*fetch_value_string(t_sh_data *shd, char **str,
								char *start, int name_len)
{
	char	*name;
	char	*value;
	size_t	st;

	st = start - *str;
	if (ft_strchr("$?", start[1]))
		value = start[1] == '$' ?
		ft_itoa(shd->process_id) : ft_itoa(shd->cmd_exit);
	else
	{
		name = ft_strsub(start, 1, name_len);
		value = get_shvar_val(name, shd->env);
		value = value ? ft_strdup(value) : NULL;
		ft_memdel((void **)&name);
	}
	insert_value_string(str, st, name_len, value);
	st += value ? ft_strlen(value) : 0;
	ft_memdel((void **)&value);
	return (*str + st);
}

void		param_exp(t_sh_data *shd, char **str)
{
	char	*ptr;
	int		name_len;
	int		qmode;

	if (!*str)
		return ;
	ptr = *str;
	qmode = NO_QUOTE;
	while (*ptr)
	{
		qmode = get_qmode(qmode, *ptr);
		name_len = 0;
		if (*ptr == '$' && (qmode == NO_QUOTE || qmode == DQUOTE))
			name_len = get_name(ptr + 1, qmode);
		ptr = name_len ? fetch_value_string(shd, str, ptr, name_len) : ptr + 1;
	}
	if (!**str)
		ft_memdel((void **)str);
}
