/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:29:38 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/29 15:59:39 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "g_builtins.h"
#include "ms_execution.h"

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

void		ms_execution(t_ms_data *msd, char ***cmd, int free_cmd)
{
	char	**argv;
	int		buid;

	argv = *cmd;
	if (ft_strchr(argv[0], '/'))
	{
		msd->cmd_exit = 1;
		exec_local_file(msd, argv);
	}
	else if ((buid = builtin_match(argv[0])) >= 0)
		msd->cmd_exit = g_builtins[buid].bi(argv, msd);
	else
	{
		msd->cmd_exit = 1;
		exec_on_path(msd, argv);
	}
	if (free_cmd == CMD_FREE)
	{
		ft_wtfree(argv);
		*cmd = NULL;
	}
}
