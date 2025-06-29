/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:54:42 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 14:26:07 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	execute_builtin(t_command *cmd, char ***env)
{
	char	*command;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	command = cmd->args[0];
	if (strcmp(command, "cat") == 0 && !cmd->args[1])
		printf("minishell: cat: waiting for input (Ctrl+D to exit)\n");
	else if (strcmp(command, "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (strcmp(command, "cd") == 0)
		return (builtin_cd(cmd->args));
	else if (strcmp(command, "pwd") == 0)
		return (builtin_pwd());
	else if (strcmp(command, "export") == 0)
		return (builtin_export(cmd->args, env));
	else if (strcmp(command, "unset") == 0)
		return (builtin_unset(cmd->args));
	else if (strcmp(command, "env") == 0)
		return (builtin_env(*env));
	else if (strcmp(command, "exit") == 0)
		return (builtin_exit(cmd->args));
	return (0);
}

static int	handle_parent_process(pid_t pid, char *binary_path)
{
	int	status;

	waitpid(pid, &status, 0);
	free(binary_path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_external_command(t_command *cmd, char ***envp)
{
	char	*binary_path;
	pid_t	pid;
	int		result;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (cmd->args[0][0] == '\0')
	{
		shift_args(cmd);
		if (!cmd->args[0])
			return (0);
	}
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
		result = handle_path_command(cmd, &binary_path);
	else
		result = handle_regular_command(cmd, &binary_path);
	if (result != 0)
		return (result);
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, binary_path, envp);
	else if (pid > 0)
		return (handle_parent_process(pid, binary_path));
	else
	{
		perror("fork");
		free(binary_path);
		return (1);
	}
	return (0);
}