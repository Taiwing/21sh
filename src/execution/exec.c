/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:33:05 by yforeau           #+#    #+#             */
/*   Updated: 2019/04/18 00:34:20 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_data.h"
#include "t_shvar.h"
#include "ms_signals.h"

static int		wait_cp(pid_t cp, char *name)
{
	int		status;

	status = 0;
	if (waitpid(cp, &status, WUNTRACED) == -1)
		ft_putstr_fd("minishell: wait() error\n", 2);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
		ft_dprintf(0, "\nProcess %d (%s) stopped\n", cp, name);
	return (status);
}

static int		exec_file(char *file_path, char **argv, char **env)
{
	pid_t	cp;
	int		ret;

	cp = 0;
	ret = 1;
	if ((cp = fork()) == -1)
		ft_putstr_fd("minishell: error while forking ;)\n", 2);
	else if (!cp)
	{
		reset_input_mode();
		if (execve(file_path, argv, env) == -1)
			ft_putstr_fd("minishell: execve() error\n", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		stat_pid(cp);
		ret = wait_cp(cp, argv[0]);
		set_custom_input_mode();
		stat_pid(-1);
	}
	return (ret);
}

void			exec_local_file(t_ms_data *msd, char **argv)
{
	char	**env;

	if (access(argv[0], F_OK) == -1)
		ft_dprintf(2, "minishell: %s: command not found\n", argv[0]);
	else if (access(argv[0], X_OK) == -1)
		ft_dprintf(2, "minishell: %s: permission denied\n", argv[0]);
	else
	{
		env = list_to_env(msd->env);
		msd->cmd_exit = exec_file(argv[0], argv, env);
		ft_wtfree(env);
	}
}

void			exec_on_path(t_ms_data *msd, char **argv)
{
	char	*fp;
	char	**wt;

	wt = msd->path;
	while (wt && *wt)
	{
		fp = ft_strnew(ft_strlen(*wt) + 1 + ft_strlen(argv[0]));
		ft_strcat(ft_strcat(ft_strcat(fp, *wt), "/"), argv[0]);
		if (!access(fp, F_OK))
		{
			if (access(fp, X_OK) == -1)
				ft_dprintf(2, "minishell: %s: permission denied\n", argv[0]);
			else
			{
				wt = list_to_env(msd->env);
				msd->cmd_exit = exec_file(fp, argv, wt);
				ft_wtfree(wt);
			}
			ft_memdel((void **)&fp);
			return ;
		}
		ft_memdel((void **)&fp);
		++wt;
	}
	ft_dprintf(2, "minishell: %s: command not found\n", argv[0]);
}
