/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msb_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:25:01 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 14:25:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"
#include "ms_data.h"
#include "quotes.h"

static char	*get_alias_name(char *str)
{
	char	*delim;

	if (!str || !(delim = ft_strchr(str, '=')) || delim == str)
	{
		if (!str || delim == str)
			ft_putstr_fd("alias: invalid alias name\n", 2);
		else
			ft_putstr_fd("alias: empty alias\n", 2);
		return (NULL);
	}
	return (ft_strsub(str, 0, delim - str));
}

static void	print_alias_list(t_list *lst)
{
	t_shvar	*svar;

	while (lst)
	{
		svar = (t_shvar *)lst->content;
		ft_printf("alias %s='%s'\n", svar->name, svar->value);
		lst = lst->next;
	}
}

int			msb_alias(char **argv, t_ms_data *msd)
{
	int		argc;
	char	*name;
	char	*value;

	if ((argc = ft_wtlen(argv)) == 1)
		print_alias_list(msd->alias);
	else if (argc > 2)
	{
		ft_putstr_fd("alias: too many arguments\n", 2);
		return (1);
	}
	else if ((name = get_alias_name(argv[1])))
	{
		value = unquote_str(ft_strchr(argv[1], '=') + 1);
		set_shvar(name, value, &msd->alias, ALIAS_VAR);
		ft_memdel((void **)&name);
		ft_memdel((void **)&value);
	}
	return (0);
}
