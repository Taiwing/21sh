#include "sh_parsing.h"
#include "g_builtins.h"

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

static char	*find_path_file(char **wt, char *cmd_name)
{
	char	*fp;

	fp = NULL;
	while (wt && *wt)
	{
		fp = ft_strnew(ft_strlen(*wt) + 1 + ft_strlen(cmd_name));
		ft_strcat(ft_strcat(ft_strcat(fp, *wt), "/"), cmd_name);
		if (!access(fp, F_OK))
		{
			if (access(fp, X_OK) == -1)
			{
				ft_dprintf(2, SHELL_NAME": %s: permission denied\n", cmd_name);
				ft_memdel((void **)&fp);
			}
			return (fp);
		}
		ft_memdel((void **)&fp);
		++wt;
	}
	ft_dprintf(2, SHELL_NAME": %s: command not found\n", cmd_name);
	return (fp);
}

static int	access_test(char *cmd_name)
{
	if (access(cmd_name, F_OK))
		ft_dprintf(2, SHELL_NAME": %s: command not found\n", cmd_name);
	else if (access(cmd_name, X_OK) == -1)
		ft_dprintf(2, SHELL_NAME": %s: permission denied\n", cmd_name);
	else
		return (0);
	return (1);
}

int		find_command(t_sh_data *shd, t_command *cmd, char *cmd_name)
{
	int		buid;
	char		*local;

	if ((buid = builtin_match(cmd_name)) >= 0)
	{
		cmd->cmd_path = NULL;
		cmd->type = CT_BUILTIN;
		cmd->buid = buid;
	}
	else if ((local = ft_strchr(cmd_name, '/')) && !access_test(cmd_name))
	{
		cmd->cmd_path = ft_strdup(cmd_name);
		cmd->type = CT_LOCAL_FILE;
	}
	else if (!local && (cmd_name = find_path_file(shd->path, cmd_name)))
	{
		cmd->cmd_path = cmd_name;
		cmd->type = CT_PATH_FILE;
	}
	else
		return (1);
	return (0);
}
