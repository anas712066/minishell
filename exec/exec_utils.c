#include "../include/exec.h"

static char	*search_in_path(const char *command, char *path_copy)
{
	char	*dir;
	char	full_path[1024];

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (ft_strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

char	*find_binary_in_path(const char *command)
{
	char	*path;
	char	*path_copy;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	if (!path_copy)
	{
		perror("strdup");
		return (NULL);
	}
	return (search_in_path(command, path_copy));
}

void	shift_args(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i + 1])
	{
		cmd->args[i] = cmd->args[i + 1];
		i++;
	}
	cmd->args[i] = NULL;
}

int	handle_path_command(t_command *cmd, char **binary_path)
{
	struct stat	st;

	if (stat(cmd->args[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd->args[0], strlen(cmd->args[0]));
			write(STDERR_FILENO, ": Is a directory\n", 16);
			return (126);
		}
		if (access(cmd->args[0], X_OK) != 0)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd->args[0], strlen(cmd->args[0]));
			write(STDERR_FILENO, ": Permission denied\n", 20);
			return (126);
		}
	}
	else
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd->args[0], strlen(cmd->args[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (127);
	}
	*binary_path = ft_strdup(cmd->args[0]);
	return (0);
}

int	handle_regular_command(t_command *cmd, char **binary_path)
{
	struct stat	st;

	*binary_path = find_binary_in_path(cmd->args[0]);
	if (!*binary_path)
	{
		if (stat(cmd->args[0], &st) == 0)
		{
			if (S_ISDIR(st.st_mode) || access(cmd->args[0], X_OK) != 0)
			{
				write(STDERR_FILENO, " command not found", 18);
				return (127);
			}
			*binary_path = ft_strdup(cmd->args[0]);
		}
		else
		{
			write(STDERR_FILENO, " command not found\n", 19);
			write(STDERR_FILENO, "\n", 1);
			return (127);
		}
	}
	return (0);
}
