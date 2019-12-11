/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:12:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 20:58:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "sh_data.h"

void	exec_local_file(t_sh_data *shd, char **argv);
void	exec_on_path(t_sh_data *shd, char **argv);

#endif
