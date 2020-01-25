#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

char	*g_path[7] = {
	"/usr/local/bin/",
	"/usr/local/sbin/",
	"/usr/bin/",
	"/bin/",
	"/usr/sbin/",
	"/sbin/",
	NULL
};

static void	find_cmd_name(char *argv_0, char cmd_name[256])
{
	int	i;

	i = -1;
	strncpy(cmd_name, argv_0, 255);
	while (access(cmd_name, X_OK) < 0 && g_path[++i])
	{
		strncpy(cmd_name, g_path[i], 255);
		strncat(cmd_name, argv_0, 255 - strlen(g_path[i]));
	}
	if (i != -1 && !g_path[i])
		bzero(cmd_name, 256);
}

static int	exec_command(char cmd_name[256], char **argv, char **env, int fd[2])
{
	int	in;
	int	out;

	in = fd[0];
	out = fd[1];
	find_cmd_name(argv[0], cmd_name);
	if (!cmd_name[0])
		fprintf(stderr, "error: '%s' not found\n", argv[0]);
	if (in != 0)
	{
		if (dup2(in, 0) == -1)
			perror("dup2");
		close(in);
	}
	if (out != 1)
	{
		if (dup2(out, 1) == -1)
			perror("dup2");
		close(out);
	}
	if (execve(cmd_name, argv, env) == -1)
		perror("execve");
	return (1);
}

static int	spawn_process(char **argv, char **env, int in, int out)
{
	pid_t	cp;
	int		ret;
	int		fd[2];
	char	**ptr;
	char	cmd_name[256];

	cp = 0;
	ret = 0;
	printf("trying to exec '");
	ptr = argv;	
	bzero(cmd_name, 256);
	fd[0] = in;
	fd[1] = out;
	while (*ptr)
	{
		printf("%s%s", *ptr, *(ptr + 1) ? " " : "'\n");
		++ptr;
	}
	if ((cp = fork()) == -1)
	{
		perror("fork");
		return (1);
	}
	else if (!cp)
		return (exec_command(cmd_name, argv, env, fd));
	return (0);
}

static char	**ft_split_whitespaces(char *str)
{
	static int	size = 0;
	int			l;
	char		*p;
	char		**tb;

	if (!str)
		return (NULL);
	p = NULL;
	tb = NULL;
	size = size == -1 ? 1 : size + 1;
	while (*str && (*str == 32 || (*str > 8 && *str < 12)))
		++str;
	l = 0;
	while (str[l] && !(str[l] == 32 || (str[l] > 8 && str[l] < 12)))
		++l;
	if (l && !(p = strndup(str, l)))
		size = -1;
	if (size != -1 && !(tb = p ? ft_split_whitespaces(str + l) :
		(char **)malloc(size * sizeof(char *))))
		size = -1;
	if (size == -1 && p)
		free(p);
	else if (size != -1)
		tb[--size] = p;
	return (tb);
}

static void	ft_wtfree(char **wt)
{
	char	**ptr;

	if (!wt)
		return ;
	ptr = wt;
	while (*wt)
		free(*wt++);
	free(ptr);
}

static char	***build_commands(char *last_command)
{
	static int	size = 0;
	char		***commands;
	char		**cmd;
	char		*pipe_sym;
	char		*cmd_str;

	size = size < 0 ? 1 : size + 1;
	cmd = NULL;
	cmd_str = NULL;
	commands = NULL;
	pipe_sym = NULL;
	if (last_command && (pipe_sym = strchr(last_command, '|')))
		cmd_str = strndup(last_command, pipe_sym++ - last_command);
	else if (last_command)
		cmd_str = strdup(last_command);
	if (last_command && (!cmd_str || !(cmd = ft_split_whitespaces(cmd_str))))
		size = -1;
	free(cmd_str);
	if (cmd || size > 1)
		commands = last_command ? build_commands(pipe_sym) :
			(char ***)malloc(size * sizeof(char **));
	if (size != -1)
		commands[--size] = cmd;
	else if (cmd)
		ft_wtfree(cmd);
	return (commands);
}

static void	ft_print_words_tables(char **tab)
{
	while (*tab)
		printf("%s\n", *tab++);
}

static void	exec_pipeline(char ***cmd, char **env)
{
	int		i;
	int		in;
	int		fd[2];

	i = -1;
	in = 0;
	fd[0] = 0;
	while (cmd[++i])
	{
		fd[1] = 1;
		if (cmd[i+1] && pipe(fd) != 0)
		{
			perror("pipe");
			continue ;
		}
		printf("command %d:\n", i + 1);
		spawn_process(cmd[i], env, in, fd[1]);
		if (in != 0)
			close(in);
		if (fd[1] != 1)
			close(fd[1]);
		in = fd[0];
		ft_wtfree(cmd[i]);
	}
	free(cmd);
}

int			main(int argc, char **argv, char **env)
{
	char	***cmd;

	if (argc != 2)
	{
		printf("usage: %s 'PIPELINE'\n", argv[0]);
		return (1);
	}
	if (!(cmd = build_commands(argv[1])))
	{
		fprintf(stderr, "%s: build_commands error\n", argv[0]);
		return (1);
	}
	else
		exec_pipeline(cmd, env);
	return (0);
}
