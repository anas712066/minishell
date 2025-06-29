/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:54:42 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 19:06:35 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	handle_local_file(const char *command, char **binary_path)
{
	struct stat	st;

	if (stat(command, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write(STDERR_FILENO, " command not found", 18);
			return (127);
		}
		if (access(command, X_OK) != 0)
		{
			write(STDERR_FILENO, " command not found", 18);
			return (127);
		}
		*binary_path = ft_strdup(command);
		return (0);
	}
	write(STDERR_FILENO, " command not found\n", 19);
	write(STDERR_FILENO, "\n", 1);
	return (127);
}

static int	execute_child_process(t_command *cmd,
	char *binary_path, char ***envp)
{
	if (handle_redirections(cmd) != 0)
	{
		free(binary_path);
		exit(1);
	}
	if (execve(binary_path, cmd->args, *envp) == -1)
	{
		perror("execve failed");
		free(binary_path);
		exit(1);
	}
	return (0);
}

static int	resolve_binary_path(t_command *cmd, char **binary_path)
{
	int	ret;

	*binary_path = NULL;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (handle_empty_command(cmd))
		return (0);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		ret = check_file_permissions(cmd->args[0]);
		if (ret != 0)
			return (ret);
		*binary_path = ft_strdup(cmd->args[0]);
		return (0);
	}
	else
	{
		*binary_path = find_binary_in_path(cmd->args[0]);
		if (!*binary_path)
			return (handle_local_file(cmd->args[0], binary_path));
	}
	return (0);
}

static int	execute_fork_process(t_command *cmd, char *binary_path,
	char ***envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, binary_path, envp);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(binary_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		return (1);
	}
	else
	{
		perror("fork");
		free(binary_path);
		return (1);
	}
	return (1);
}

int	execute_external_command(t_command *cmd, char ***envp)
{
	char	*binary_path;
	int		resolve_result;

	resolve_result = resolve_binary_path(cmd, &binary_path);
	if (resolve_result != 0)
		return (resolve_result);
	if (!binary_path)
		return (1);
	return (execute_fork_process(cmd, binary_path, envp));
}
