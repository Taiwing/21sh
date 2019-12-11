/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shvar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 20:15:11 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 15:42:02 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SHVAR_H
# define T_SHVAR_H

# define ENV_VAR		0x01
# define ENV_LOCAL_VAR	0x02
# define ALIAS_VAR		0x03

# include "libft.h"

typedef struct	s_shvar
{
	char		*name;
	char		*value;
	int			type;
}				t_shvar;

int				shvar_cmp(void *svar1, void *svar2);
int				name_shvar_cmp(void *name, void *svar);
void			shvar_del(void *content, size_t content_size);
t_shvar			*get_shvar(char *name, t_list *env);
char			*get_shvar_val(char *name, t_list *env);
void			set_shvar(const char *name, const char *value,
						t_list **env, int type);
t_shvar			*str_to_env(t_shvar *dest, char *str);
t_list			*env_to_list(char **env);
char			**list_to_env(t_list *lst);

#endif
