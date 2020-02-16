/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:03:33 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/16 14:20:07 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXING_H
# define SH_LEXING_H

# include "sh_data.h"

# define HISTORY_OFF	0
# define HISTORY_ON		1

t_list	*sh_lexing(t_sh_data *shd, char **input, int history);

#endif
