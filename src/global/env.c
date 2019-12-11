/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:50:06 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 12:18:02 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_shvar.h"

t_shvar	*str_to_env(t_shvar *dest, char *str)
{
	char *delim;

	if (!str || !(delim = ft_strchr(str, '=')) || delim == str)
		return (NULL);
	dest->name = ft_strsub(str, 0, delim - str);
	dest->value = delim[1] ?
		ft_strsub(delim + 1, 0, ft_strlen(delim + 1)) : NULL;
	dest->type = ENV_VAR;
	return (dest);
}

t_list	*env_to_list(char **env)
{
	t_list	*lst;
	t_shvar	envar;

	lst = NULL;
	while (*env)
	{
		if (str_to_env(&envar, *env))
			ft_lst_sorted_insert(&lst,
				ft_lstnew((void *)&envar, sizeof(t_shvar)), shvar_cmp);
		++env;
	}
	return (lst);
}

char	**list_to_env(t_list *lst)
{
	int		i;
	int		size;
	char	**env;
	t_shvar	*svar;

	if (!(size = ft_lst_size(lst)))
		return (NULL);
	env = ft_secmalloc((size + 1) * sizeof(char *));
	i = -1;
	while (++i < size)
	{
		svar = (t_shvar *)lst->content;
		env[i] = !(svar->name && svar->value) ? ft_strjoin(svar->name, "=") :
			ft_strnew(ft_strlen(svar->name) + ft_strlen(svar->value) + 1);
		if (svar->value)
		{
			ft_strcat(env[i], svar->name);
			ft_strcat(env[i], "=");
			ft_strcat(env[i], svar->value);
		}
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}
