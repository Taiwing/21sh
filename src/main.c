/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 21:58:02 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/16 14:17:46 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_input.h"
#include "sh_lexing.h"
#include "sh_parsing.h"
#include "sh_execution.h"

int		main(int argc, char **argv, char **env)
{
	t_sh_data	shd;
	char		*input;
	t_list		*tokens;
	t_cmd_list	*exec_tree;

	(void)argc;
	(void)argv;
	input = NULL;
	tokens = NULL;
	exec_tree = NULL;
	sh_init(&shd, env);
	while (1)
	{
		if (!input)
			input = sh_input(&shd, 0, 0);
		if (input)
		{
			if ((tokens = sh_lexing(&shd, &input, HISTORY_ON)))
			{
				if ((exec_tree = sh_parsing(&shd, tokens)))
				{
					sh_execution(&shd, exec_tree);
					destroy_exec_tree(exec_tree);
				}
				destroy_token_list(&tokens);
			}
			ft_memdel((void **)&input);
		}
	}
	return (0);
}
