/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:46:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/17 16:52:14 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTION_H
# define MS_EXECUTION_H

# include "ms_data.h"

enum	e_cmdfree {CMD_FREE, CMD_KEEP};

void	ms_execution(t_ms_data *msd, char ***cmd, int free_cmd);

#endif
