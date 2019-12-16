/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:32:04 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 22:44:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSING_H
# define SH_PARSING_H

# include "sh_data.h"
# include "token.h"

# define PRODS_COUNT 21

enum 				e_prods {P_COMPLETE_COMMAND, P_LIST, P_LIST_P, P_AND_OR,
						P_AND_OR_P, P_PIPELINE, P_PIPELINE_P, P_COMMAND,
						P_CMD_NAME, P_CMD_WORD, P_CMD_PREFIX, P_CMD_SUFFIX,
						P_IO_REDIRECT, P_IO_FILE, P_FILENAME, P_IO_HERE,
						P_HERE_END, P_NEWLINE_LIST, P_LINEBREAK, P_SEPARATOR,
						P_TERM};

/*
** This is the maximum number of sub grammar rules a rule has. It could
** change if new grammar rules are added.
*/

# define SUB_SYMBOLS_MAX 3

typedef struct		s_node
{
	enum e_prods	id;
	enum e_tokenid	t_id;
	char			*str;
	struct s_node	*nodes[SUB_SYMBOLS_MAX + 1];
}					t_node;

void				destroy_tree(t_node *root, int destroy_root);
int					accept_prod(enum e_prods prod, enum e_tokenid t_id,
						t_list **token, t_node **parent);
int					expect_prod(enum e_prods prod, enum e_tokenid t_id,
						t_list **token, t_node **parent);
t_node				*sh_parsing(t_sh_data *shd, t_list **tokens);

extern int			(* const g_p_functions[PRODS_COUNT])(enum e_tokenid t_id,
					t_list **token, t_node *node);

extern int			p_complete_command(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_list(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_list_p(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_and_or(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_and_or_p(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_pipeline(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_pipeline_p(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_command(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_cmd_name(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_cmd_word(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_cmd_prefix(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_cmd_suffix(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_io_redirect(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_io_file(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_filename(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_io_here(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_here_end(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_newline_list(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_linebreak(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_separator(enum e_tokenid t_id,
						t_list **token, t_node *node);
extern int			p_term(enum e_tokenid t_id,
						t_list **token, t_node *node);

#endif
