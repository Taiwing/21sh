/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dllst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 20:04:17 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/20 17:29:40 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DLLST_H
# define T_DLLST_H

# include <stddef.h>

typedef struct		s_dllst
{
	struct s_dllst	*prev;
	struct s_dllst	*next;
	char			c;
}					t_dllst;

t_dllst				*dllst_new(char c);
t_dllst				*dllst_insert_forwd(t_dllst **alst, char c);
t_dllst				*dllst_insert_back(t_dllst **alst, char c);
void				dllst_remove_back(t_dllst **alst);
void				dllst_remove_forwd(t_dllst **alst);
void				dllst_del(t_dllst *lst);
t_dllst				*dllst_first(t_dllst *lst);
t_dllst				*dllst_last(t_dllst *lst);
size_t				dllstlen(t_dllst *lst);
char				*dllst_to_str(t_dllst *lst);
char				*dllst_to_nstr(t_dllst *lst, size_t size);
t_dllst				*str_to_dllst(char *str);
size_t				dllst_print(t_dllst *lst);

#endif
