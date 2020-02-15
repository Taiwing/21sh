#include "sh_parsing.h"

t_node			*fetch_prod(t_node *parent, enum e_prods prod)
{
	t_node	**ptr;

	ptr = parent->nodes;
	while (*ptr)
	{
		if ((*ptr)->id == prod)
			return (*ptr);
		++ptr;
	}
	return (NULL);
}

static t_command	*build_pipeline_command(t_sh_data *shd,
		t_node *pipeline_node)
{
	t_command	*next;
	t_command	*command;

	next = NULL;
	if (pipeline_node->nodes[1] && !(next = build_pipeline_command(shd,
		fetch_prod(pipeline_node->nodes[1], P_PIPELINE))))
		return (NULL);
	if ((command = build_command(shd, pipeline_node->nodes[0])))
		command->next = next;
	else if (next)
		destroy_command(next);
	return (command);
}

static t_and_or		*build_and_or(t_sh_data *shd, t_node *and_or_node,
				enum e_and_or_type type, t_and_or *left)
{
	t_command	*right;
	t_and_or	*and_or;

	if (!(right = build_pipeline_command(shd, and_or_node->nodes[0])))
	{
		destroy_and_or(left);
		return (NULL);
	}
	and_or = ft_memalloc(sizeof(t_and_or));
	and_or->left = left;
	and_or->right = right;
	and_or->type = type;
	if (and_or_node->nodes[1])
	{
		type = and_or_node->nodes[1]->nodes[0]->t_id == I_AND_IF
			? AO_TYPE_AND : AO_TYPE_OR;
		return (build_and_or(shd, fetch_prod(and_or_node->nodes[1], P_AND_OR),
			type, and_or));
	}
	return (and_or);
}

static t_cmd_list	*build_cmd_list(t_sh_data *shd, t_node *list_node)
{
	t_and_or	*cur;
	t_cmd_list	*next;
	t_cmd_list	*cmd_list;

	cur = NULL;
	next = NULL;
	cmd_list = NULL;
	if ((cur = build_and_or(shd, list_node->nodes[0], AO_TYPE_NONE, NULL)))
		cmd_list = ft_memalloc(sizeof(t_cmd_list));
	if (list_node->nodes[1])
		next = build_cmd_list(shd, list_node->nodes[1]->nodes[1]);
	if (cmd_list)
	{
		cmd_list->cur = cur;
		cmd_list->next = next;
		return (cmd_list);
	}
	return (next);
}

t_cmd_list		*build_exec_tree(t_sh_data *shd, t_node *root)
{
	t_cmd_list	*exec_tree;

	exec_tree = build_cmd_list(shd, root->nodes[0]);
	destroy_tree(root, 1);
	return (exec_tree);
}
