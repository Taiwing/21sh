#include "sh_parsing.h"

void	destroy_command(t_command *command)
{
	if (!command)
		return ;
	ft_wtfree(command->argv);
	if (command->cmd_path)
		ft_memdel((void **)&command->cmd_path);
	if (command->next)
		destroy_command(command->next);
	ft_memdel((void **)&command);
}

void	destroy_and_or(t_and_or *and_or)
{
	if (!and_or)
		return ;
	if (and_or->left)
		destroy_and_or(and_or->left);
	destroy_command(and_or->right);
	ft_memdel((void **)&and_or);
}

void	destroy_exec_tree(t_cmd_list *cmd_list)
{
	if (!cmd_list)
		return ;
	if (cmd_list->next)
		destroy_exec_tree(cmd_list->next);
	destroy_and_or(cmd_list->cur);
	ft_memdel((void **)&cmd_list);
}
