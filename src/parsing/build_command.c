#include "sh_parsing.h"

/*
** TODO: (maybe) add alias and multi-word expansions from variables
** else, the alias builtin will have to be deleted
*/

static void	add_prefix(t_sh_data *shd, t_list **redirs, t_node *prefix_node)
{
	if (!prefix_node)
		return ;
	//TODO: parse redirections into a usable structure instead of doing that
	ft_lst_push_back(redirs, NULL, 0)->content = prefix_node->nodes[0];
	add_prefix(shd, redirs, fetch_prod(prefix_node, P_CMD_PREFIX));
}

static void	add_suffix(t_sh_data *shd, t_list **redirs, t_list **args,
		t_node *suffix_node)
{
	char	*arg;
	t_node	*suffix;

	if (!suffix_node)
		return ;
	if ((suffix = fetch_prod(suffix_node, P_CMD_WORD)))
	{
		if ((arg = expand(shd, suffix->nodes[0]->str)))
			ft_lst_push_back(args, NULL, 0)->content = arg;
	}
	//TODO: parse redirections into a usable structure instead of doing that
	else if ((suffix = fetch_prod(suffix_node, P_IO_REDIRECT)))
		ft_lst_push_back(redirs, NULL, 0)->content = suffix;
	add_suffix(shd, redirs, args, fetch_prod(suffix_node, P_CMD_SUFFIX));
}

static char	**build_argv(t_list *args)
{
	static int	len = 0;
	char		**argv;
	char		*arg;

	++len;
	argv = NULL;
	if (args)
	{
		arg = args->content;
		argv = build_argv(args->next);
		args->content = NULL;
		ft_memdel((void **)&args);
	}
	else
	{
		arg = NULL;
		argv = ft_memalloc(len * sizeof(char *));
	}
	argv[--len] = arg;
	return (argv);
}

//TODO: actually parse the redirection into something usable
//for now this is just a placeholder which destroys the list
//(it basically does the exact inverse of what its name says)
//also: this probably will have to stop the command build in
//case of errors in the redirections
static void	build_redirs(t_list *redirs)
{
	if (!redirs)
		return ;
	build_redirs(redirs->next);
	redirs->content = NULL;
	ft_memdel((void **)&redirs);
}

t_command	*build_command(t_sh_data *shd, t_node *command_node)
{
	t_command	cmd;
	t_list		*args;
	t_list		*redirs;
	char		*cmd_name;

	args = NULL;
	redirs = NULL;
	ft_bzero((void *)&cmd, sizeof(t_command));
	cmd_name = fetch_prod(command_node, P_CMD_NAME)->nodes[0]->str;
	if (!(cmd_name = expand(shd, cmd_name)))
		return (NULL);
	if (find_command(shd, &cmd, cmd_name))
	{
		ft_memdel((void **)&cmd_name);
		return (NULL);
	}
	ft_lst_push_back(&args, NULL, 0)->content = cmd_name;
	add_prefix(shd, &redirs, fetch_prod(command_node, P_CMD_PREFIX));
	add_suffix(shd, &redirs, &args, fetch_prod(command_node, P_CMD_SUFFIX));
	cmd.argv = build_argv(args);
	build_redirs(redirs);
	return (ft_memcpy(ft_secmalloc(sizeof(t_command)), &cmd, sizeof(t_command)));
}
