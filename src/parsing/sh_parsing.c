/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 10:28:46 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 22:45:23 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parsing.h"
#include "debug.h"

int			(* const g_p_functions[PRODS_COUNT])(enum e_tokenid t_id,
			t_list **token, t_node *node) = {
	p_complete_command,
	p_list,
	p_list_p,
	p_and_or,
	p_and_or_p,
	p_pipeline,
	p_pipeline_p,
	p_command,
	p_cmd_name,
	p_cmd_word,
	p_cmd_prefix,
	p_cmd_suffix,
	p_io_redirect,
	p_io_file,
	p_filename,
	p_io_here,
	p_here_end,
	p_newline_list,
	p_linebreak,
	p_separator,
	p_term
};

static void	add_node(t_node *src, t_node **parent)
{
	t_node	**place;
	t_node	*new_node;

	new_node = ft_memalloc(sizeof(t_node));
	ft_memcpy((void *)new_node, (void *)src, sizeof(t_node));
	place = !*parent ? parent : (*parent)->nodes;	
	while (*place)
		++place;
	*place = new_node;
}

void		destroy_tree(t_node *root, int destroy_root)
{
	t_node	**sub_trees;

	if (root->str)
		ft_memdel((void **)&root->str);
	sub_trees = root->nodes;
	while (*sub_trees)
	{
		destroy_tree(*sub_trees, 1);
		++sub_trees;
	}
	if (destroy_root)
		ft_memdel((void **)&root);
}

int			expect_prod(enum e_prods prod, enum e_tokenid t_id,
				t_list **token, t_node **parent)
{
	t_list	*sub_token;
	t_node	new_node;

	ft_bzero((void *)&new_node, sizeof(t_node));
	new_node.id = prod;
	new_node.t_id = t_id;
	sub_token = *token;
	if (g_p_functions[prod](t_id, &sub_token, &new_node))
	{
		add_node(&new_node, parent);
		*token = sub_token;
		return (1);
	}
	destroy_tree(&new_node, 0);
	return (0);
}

int			accept_prod(enum e_prods prod, enum e_tokenid t_id,
				t_list **token, t_node **parent)
{
	t_list	*sub_token;
	t_node	new_node;

	ft_bzero((void *)&new_node, sizeof(t_node));
	new_node.id = prod;
	new_node.t_id = t_id;
	sub_token = *token;
	if (g_p_functions[prod](t_id, &sub_token, &new_node))
	{
		add_node(&new_node, parent);
		*token = sub_token;
		return (1);
	}
	destroy_tree(&new_node, 0);
	return (0);
}

t_cmd_list		*sh_parsing(t_sh_data *shd, t_list **tokens)
{
	t_node		*root;
	t_list		*token;

	(void)shd;
	root = NULL;
	token = *tokens;
	if (!expect_prod(P_COMPLETE_COMMAND, I_NONE, &token, &root))
		ft_printf(SHELL_NAME": parsing error\n");
	return (root ? build_exec_tree(shd, root) : NULL);
}
