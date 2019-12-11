/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 21:58:02 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/21 14:44:10 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"
#include "ms_lexing.h"
#include "ms_parsing.h"
#include "ms_execution.h"

int		main(int argc, char **argv, char **env)
{
	t_ms_data	msd;
	char		**cmd;
	char		*input;
	t_list		*cmd_list;

	(void)argc;
	(void)argv;
	cmd = NULL;
	input = NULL;
	cmd_list = NULL;
	ms_init(&msd, env);
	while (1)
	{
		if (!input)
			input = ms_input(&msd, 0, 0);
		if (input)
			cmd_list = ms_lexing(&msd, &input);
		while (cmd_list)
		{
			if ((cmd = ms_parsing(&msd, &cmd_list)))
				ms_execution(&msd, &cmd, CMD_FREE);
		}
	}
	return (0);
}
