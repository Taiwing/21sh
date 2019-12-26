/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:54:29 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/20 19:04:08 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_DATA_H
# define SH_DATA_H

# include "libft.h"

# define HISTMAX	2048
# define CMDMAX		4097
# define SHELL_NAME	"21sh"

typedef struct		s_sh_history
{
	char			*cmd[HISTMAX];
	size_t			size;
}					t_sh_history;

void				load_history(t_sh_history *hist, char *home_path);
void				add_to_history(char *input, t_sh_history *hist,
						char *path, size_t *cmd_c);
void				del_history(t_sh_history *hist, size_t start, size_t len);
void				write_history(int fd, t_sh_history *hist,
						size_t start, size_t len);
void				flush_history(t_sh_history *hist,
						size_t len, char *path);

typedef struct		s_sh_data
{
	t_list			*env;
	t_list			*alias;
	char			**path;
	int				cmd_exit;
	int				process_id;
	t_sh_history	hist;
	size_t			cmd_c;
	int				term_width;
	int				ppt;
	char			*cm_cap;
}					t_sh_data;

void				reset_input_mode(void);
void				set_custom_input_mode(void);
void				sh_init(t_sh_data *shd, char **env);

#endif
