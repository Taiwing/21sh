/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 21:58:02 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/16 01:31:14 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_input.h"
#include "sh_lexing.h"
#include "sh_parsing.h"
#include "sh_execution.h"
#include "debug.h"

int		main(int argc, char **argv, char **env)
{
	t_sh_data	shd;
	char		*input;
	t_list		*tokens;
//	t_node		*parse_tree;

	(void)argc;
	(void)argv;
	input = NULL;
	tokens = NULL;
//	parse_tree = NULL;
	sh_init(&shd, env);
	while (1)
	{
		if (!input)
			input = sh_input(&shd, 0, 0);
		if (input)
		{
			if ((tokens = sh_lexing(&shd, &input)))
			{	
				while (tokens)
				{
					show_token(tokens->content);
					discard_token(&tokens);
				}
			}
//				parse_tree = sh_parsing(&shd, &tokens);
			ft_memdel((void **)&input);
/*			if (parse_tree)
				sh_execution(&shd, &parse_tree, CMD_FREE); */
		}
	}
	return (0);
}
