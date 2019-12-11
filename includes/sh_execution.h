/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:46:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 20:59:22 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXECUTION_H
# define SH_EXECUTION_H

# include "sh_data.h"

enum	e_cmdfree {CMD_FREE, CMD_KEEP};

void	sh_execution(t_sh_data *shd, char ***cmd, int free_cmd);

#endif
