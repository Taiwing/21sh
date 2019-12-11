/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:03:33 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 20:59:55 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXING_H
# define SH_LEXING_H

# include "sh_data.h"

t_list	*sh_lexing(t_sh_data *shd, char **input);

#endif
