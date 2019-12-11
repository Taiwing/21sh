/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_completion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 13:41:26 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/20 18:43:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAB_COMPLETION_H
# define TAB_COMPLETION_H

# include "ms_input.h"

enum	e_comp {NO_COMP, ENV_COMP, EXEC_COMP, FILE_COMP};

int		check_completion(t_input_data *idat, char **part);
void	complete_input(int completion, char *part,
			t_input_data *idat, t_ms_data *msd);
char	*env_completion(char *part, t_list *env);
char	*exec_completion(char *part, char **path);
char	*file_completion(char *part);
char	*part_match(char *comp, char *name, char *part, size_t len);
void	reduce_match(char *comp, char *name);

#endif
