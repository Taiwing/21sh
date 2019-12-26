/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:57:24 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/20 18:14:37 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "g_builtins.h"

const t_builtid	g_builtins[BUILTIN_COUNT] =
{
	{"alias", shb_alias},
	{"cd", shb_cd},
	{"echo", shb_echo},
	{"env", shb_env},
	{"exit", shb_exit},
	{"pwd", shb_pwd},
	{"setenv", shb_setenv},
	{"unalias", shb_unalias},
	{"unsetenv", shb_unsetenv},
	{"ptok", shb_ptok},
	{"ppt", shb_ppt}
};
