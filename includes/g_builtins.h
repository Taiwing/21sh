/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_builtins.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:00:10 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/20 18:16:08 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_BUILTINS_H
# define G_BUILTINS_H

# include "sh_data.h"

# define BUILTIN_COUNT	11

typedef	int				(*t_builtin)(char **argv, t_sh_data *shd);

typedef struct			s_builtid
{
	char				*name;
	t_builtin			bi;
}						t_builtid;

extern const t_builtid	g_builtins[BUILTIN_COUNT];

int						shb_alias(char **argv, t_sh_data *shd);
int						shb_cd(char **argv, t_sh_data *shd);
int						shb_echo(char **argv, t_sh_data *shd);
int						shb_env(char **argv, t_sh_data *shd);
int						shb_exit(char **argv, t_sh_data *shd);
int						shb_pwd(char **argv, t_sh_data *shd);
int						shb_setenv(char **argv, t_sh_data *shd);
int						shb_unalias(char **argv, t_sh_data *shd);
int						shb_unsetenv(char **argv, t_sh_data *shd);
int						shb_ptok(char **argv, t_sh_data *shd);
int						shb_ppt(char **argv, t_sh_data *shd);

#endif
