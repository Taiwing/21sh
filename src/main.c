/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 21:58:02 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:13:06 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_input.h"
#include "sh_lexing.h"
#include "sh_parsing.h"
#include "sh_execution.h"

int		main(int argc, char **argv, char **env)
{
	t_sh_data	shd;
	char		**cmd;
	char		*input;
	t_list		*cmd_list;

	(void)argc;
	(void)argv;
	cmd = NULL;
	input = NULL;
	cmd_list = NULL;
	sh_init(&shd, env);
	while (1)
	{
		if (!input)
			input = sh_input(&shd, 0, 0);
		if (input)
			cmd_list = sh_lexing(&shd, &input);
		while (cmd_list)
		{
			if ((cmd = sh_parsing(&shd, &cmd_list)))
				sh_execution(&shd, &cmd, CMD_FREE);
		}
	}
	return (0);
}
