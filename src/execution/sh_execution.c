/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:29:38 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/11 21:07:27 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "g_builtins.h"
#include "sh_execution.h"

static int	builtin_match(char *name)
{
	int	i;

	i = -1;
	while (++i < BUILTIN_COUNT)
	{
		if (!ft_strcmp(name, g_builtins[i].name))
			return (i);
	}
	return (-1);
}

void		sh_execution(t_sh_data *shd, char ***cmd, int free_cmd)
{
	char	**argv;
	int		buid;

	argv = *cmd;
	if (ft_strchr(argv[0], '/'))
	{
		shd->cmd_exit = 1;
		exec_local_file(shd, argv);
	}
	else if ((buid = builtin_match(argv[0])) >= 0)
		shd->cmd_exit = g_builtins[buid].bi(argv, shd);
	else
	{
		shd->cmd_exit = 1;
		exec_on_path(shd, argv);
	}
	if (free_cmd == CMD_FREE)
	{
		ft_wtfree(argv);
		*cmd = NULL;
	}
}
