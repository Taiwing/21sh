#include "t_shvar.h"
#include "g_builtins.h"
#include "sh_parsing.h"
#include "sh_signals.h"
#include <sys/wait.h>

//TODO: normify the six functions here

static int	exec_builtin(t_sh_data *shd, t_command *command, int in_pipe)
{
	int	ret;	

	ret = g_builtins[command->buid].bi(command->argv, shd);
	if (in_pipe)
		ft_exit(NULL, ret);
	return (ret);
}

static void	exec_in_fork(t_sh_data *shd, t_command *command, int fd[2])
{
	int	in;
	int	out;
	char	**env;

	in = fd[0];
	out = fd[1];
	if (in != 0)
	{
		if (dup2(in, 0) == -1)
			ft_putstr_fd(SHELL_NAME": dup2() error\n", 2);
		close(in);
	}
	if (out != 1)
	{
		if (dup2(out, 1) == -1)
			ft_putstr_fd(SHELL_NAME": dup2() error\n", 2);
		close(out);
	}
	if (command->type == CT_BUILTIN)
		exec_builtin(shd, command, 1);
	else
	{
		env = list_to_env(shd->env);
		if (execve(command->cmd_path, command->argv, env) == -1)
			ft_putstr_fd(SHELL_NAME": execve() error\n", 2);
		ft_exit(NULL, EXIT_FAILURE);
	}
}

static int	wait_cp(pid_t cp, char *name)
{
	int		status;

	status = 0;
	if (waitpid(cp, &status, WUNTRACED) == -1)
		ft_putstr_fd(SHELL_NAME": wait() error\n", 2);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
		ft_dprintf(0, "\nProcess %d (%s) stopped\n", cp, name);
	return (status);
}

static int	spawn_process(t_sh_data *shd, t_command *command, int in_out[2])
{
	pid_t	cp;
	int	ret;

	cp = 0;
	ret = -1;
	if ((cp = fork()) == -1)
		ft_putstr_fd(SHELL_NAME": error while forking ;)\n", 2);
	else if (!cp)
	{
		reset_input_mode();
		exec_in_fork(shd, command, in_out);
	}
	else if (cp > 0)
	{
		stat_pid(cp);
		ret = command->next ? 0 : wait_cp(cp, command->argv[0]);
		set_custom_input_mode();
		stat_pid(-1);
	}
	return (ret);
}

static void	close_pipe_desc(int in_out[2], int pipe_fd[2], int ret)
{
	if (in_out[0] != 0)
		close(in_out[0]);
	if (in_out[1] != 1)
		close(in_out[1]);
	if (ret == -1 && pipe_fd[0] != 0)
		close(pipe_fd[0]);
}

int		exec_command(t_sh_data *shd, t_command *command)
{
	int		ret;
	int		in_out[2];
	int		pipe_fd[2];

	ret = 1;
	in_out[0] = 0;
	if (command->type == CT_BUILTIN && !command->next)
		return (exec_builtin(shd, command, 0));
	while (command)
	{
		pipe_fd[1] = 1;
		if (command->next && pipe(pipe_fd) != 0)
		{
			ft_putstr_fd(SHELL_NAME": pipe() error\n", 2);
			return (1);
		}
		in_out[1] = pipe_fd[1];
		ret = spawn_process(shd, command, in_out);
		close_pipe_desc(in_out, pipe_fd, ret);
		if (ret == -1)
			return (1);
		in_out[0] = pipe_fd[0];
		command = command->next;
	}
	return (ret);
}
