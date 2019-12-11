/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_builtins.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:00:10 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 11:24:40 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_BUILTINS_H
# define G_BUILTINS_H

# include "ms_data.h"

# define BUILTIN_COUNT	9

typedef	int				(*t_builtin)(char **argv, t_ms_data *msd);

typedef struct			s_builtid
{
	char				*name;
	t_builtin			bi;
}						t_builtid;

extern const t_builtid	g_builtins[BUILTIN_COUNT];

int						msb_alias(char **argv, t_ms_data *msd);
int						msb_cd(char **argv, t_ms_data *msd);
int						msb_echo(char **argv, t_ms_data *msd);
int						msb_env(char **argv, t_ms_data *msd);
int						msb_exit(char **argv, t_ms_data *msd);
int						msb_pwd(char **argv, t_ms_data *msd);
int						msb_setenv(char **argv, t_ms_data *msd);
int						msb_unalias(char **argv, t_ms_data *msd);
int						msb_unsetenv(char **argv, t_ms_data *msd);

#endif
