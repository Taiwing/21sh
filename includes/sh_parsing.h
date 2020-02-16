/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:32:04 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/16 10:10:00 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSING_H
# define SH_PARSING_H

# include "sh_data.h"
# include "token.h"
# ifdef __APPLE__
#  include <sys/syslimits.h>
# elif __linux
#  include <linux/limits.h>
# endif

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

/*
** s_node: This structure will be used to build a parse_tree, which will be a step between the tokens
** returned by the lexer function and the execution tree that will be used to execute the commands.
*/

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

/*
** Execution tree structures: every structure is a step in the execution process
** they are ordered as fallow (from bottom to top): t_command -> t_and_or -> t_cmd_list
**
** s_command:
** argc		number of words
** argv		words of the command (argv[0] is the name of the program)
** cmd_name	path of the file to be executed by execve, or builtin
** type		the cmd_name can either be a local file (if it contains a '/'),
** 		a builtin or a path_file (if there is a match in both cases)
** redirs	store the redirections of the current command (not implemented yet)
** next		next command in the pipeline if any (wait if NULL)
**
** s_and_or:
** cur		current pipeline
** next		next s_and_or (will be executed according to current pipeline output value)
** type		is this an AND or an OR, or none
**
** s_cmd_list:
** cur		current and_or
** next		next list (will be executed if it exist)
*/

enum e_cmd_type			{CT_LOCAL_FILE, CT_BUILTIN, CT_PATH_FILE};

typedef struct			s_command
{
	char			**argv;
	char			*cmd_path;
	enum e_cmd_type		type;
	int			buid;
//	t_redirections		*redirs;
	struct s_command	*next;
}				t_command;

enum e_and_or_type		{AO_TYPE_NONE, AO_TYPE_AND, AO_TYPE_OR};

typedef struct			s_and_or
{
	struct s_and_or		*left;
	t_command			*right;
	enum e_and_or_type	type;
}				t_and_or;

typedef struct			s_cmd_list
{
	t_and_or		*cur;
	struct s_cmd_list	*next;
}				t_cmd_list;

char				*expand(t_sh_data *shd, char *str);
void				destroy_command(t_command *command);
void				destroy_and_or(t_and_or *and_or);
void				destroy_exec_tree(t_cmd_list *cmd_list);
int				find_command(t_sh_data *shd, t_command *cmd,
					char *cmd_name);
t_node				*fetch_prod(t_node *parent, enum e_prods prod);
t_command			*build_command(t_sh_data *shd, t_node *command_node);
t_cmd_list			*build_exec_tree(t_sh_data *shd, t_node *root);
t_cmd_list			*sh_parsing(t_sh_data *shd, t_list *tokens);

#endif
