/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:32:04 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:00:18 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSING_H
# define SH_PARSING_H

# include "sh_data.h"

char	**sh_parsing(t_sh_data *shd, t_list **cmd_list);

#endif
