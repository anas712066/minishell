#include "../include/exec.h"

int	execute_builtin(t_command *cmd, char ***env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (strcmp(cmd->args[0], "cat") == 0 && !cmd->args[1])
		printf("minishell: cat: waiting for input (Ctrl+D to exit)\n");
	else if (strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd->args));
	else if (strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd->args, env));
	else if (strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd->args));
	else if (strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(*env));
	else if (strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd->args));
	return (0);
}

char	*check_direct_path(const char *command)
{
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	return (NULL);
}

char	*search_in_path(const char *command, char *path_copy)
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
	char	*direct_path;

	direct_path = check_direct_path(command);
	if (direct_path)
		return (direct_path);
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

int	handle_empty_command(t_command *cmd)
{
	int	i;

	if (cmd->args[0][0] != '\0')
		return (0);
	i = 0;
	while (cmd->args[i + 1])
	{
		cmd->args[i] = cmd->args[i + 1];
		i++;
	}
	cmd->args[i] = NULL;
	if (!cmd->args[0])
		return (1);
	return (0);
}