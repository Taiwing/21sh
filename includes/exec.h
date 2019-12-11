/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:12:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/12 17:02:52 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ms_data.h"

void	exec_local_file(t_ms_data *msd, char **argv);
void	exec_on_path(t_ms_data *msd, char **argv);

#endif
