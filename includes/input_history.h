/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_history.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 08:54:28 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/22 08:56:06 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HISTORY_H
# define INPUT_HISTORY_H

# include "ms_input.h"

void	save_current_line(t_input_data *idat, t_ms_history *hist);
void	restore(t_input_data *idat, t_ms_history *hist, t_ms_data *msd);

#endif
