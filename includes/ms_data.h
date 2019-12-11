/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:00:45 by yforeau           #+#    #+#             */
/*   Updated: 2019/05/04 20:03:28 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DATA_H
# define MS_DATA_H

# include "libft.h"

# define HISTMAX	2048
# define CMDMAX		4097

typedef struct		s_ms_history
{
	char			*cmd[HISTMAX];
	size_t			size;
}					t_ms_history;

void				load_history(t_ms_history *hist, char *home_path);
void				add_to_history(char *input, t_ms_history *hist,
						char *path, size_t *cmd_c);
void				del_history(t_ms_history *hist, size_t start, size_t len);
void				write_history(int fd, t_ms_history *hist,
						size_t start, size_t len);
void				flush_history(t_ms_history *hist,
						size_t len, char *path);

typedef struct		s_ms_data
{
	t_list			*env;
	t_list			*alias;
	char			**path;
	int				cmd_exit;
	int				process_id;
	t_ms_history	hist;
	size_t			cmd_c;
	int				term_width;
}					t_ms_data;

void				reset_input_mode(void);
void				set_custom_input_mode(void);
void				ms_init(t_ms_data *msd, char **env);

#endif
