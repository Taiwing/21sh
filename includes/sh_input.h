/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 21:50:15 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 20:59:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_INPUT_H
# define SH_INPUT_H

# include "sh_data.h"
# include "t_dllst.h"

enum			e_xy {X = 0, Y = 1};

typedef struct	s_input_data
{
	char		c[8];
	int			bol;
	int			qmode;
	int			word;
	t_dllst		*lst;
	char		*buf;
	int			hi;
	int			cursor_pos[2];
}				t_input_data;

char			*sh_input(t_sh_data *shd, int qmode, int word);

#endif
