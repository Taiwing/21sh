/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:40:21 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:00:31 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_SIGNALS_H
# define SH_SIGNALS_H

# include <signal.h>

pid_t	stat_pid(pid_t in);
void	signal_hand(int sig);
void	init_signals(void);

#endif
