/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:54:42 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 14:52:18 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>      // Para open(), O_RDONLY, O_WRONLY, O_CREAT, etc.
#include <string.h> 
#include <sys/wait.h>
#include <sys/stat.h>

#include "../include/exec.h"

static int	check_file_permissions(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, path, strlen(path));
			write(STDERR_FILENO, ": Is a directory\n", 16);
			return (126);
		}
		if (access(path, X_OK) != 0)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, path, strlen(path));
			write(STDERR_FILENO, ": Permission denied\n", 20);
			return (126);
		}
		return (0);
	}
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, path, strlen(path));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	return (127);
}

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

static int	execute_child_process(t_command *cmd, char *binary_path, char ***envp)
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

int	execute_external_command(t_command *cmd, char ***envp)
{
	char	*binary_path;
	pid_t	pid;
	int		status;
	int		ret;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (handle_empty_command(cmd))
		return (0);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		ret = check_file_permissions(cmd->args[0]);
		if (ret != 0)
			return (ret);
		binary_path = ft_strdup(cmd->args[0]);
	}
	else
	{
		binary_path = find_binary_in_path(cmd->args[0]);
		if (!binary_path)
			return (handle_local_file(cmd->args[0], &binary_path));
	}
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, binary_path, envp);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(binary_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	else
	{
		perror("fork");
		free(binary_path);
		return (1);
	}

    return (0);
}
