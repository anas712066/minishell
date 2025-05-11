/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:54:42 by mumajeed          #+#    #+#             */
/*   Updated: 2025/05/11 14:33:40 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/builtins.h"
#include "../include/minishell.h"
#include "../include/parser.h"

int	execute_builtin(t_command *cmd, char ***env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);

	if (strcmp(cmd->args[0], "echo") == 0)
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

	return (0); // No es un builtin, ejecutar como externo
}

char	*find_binary_in_path(const char *command) {
	char *path = getenv("PATH");
	if (!path) {
		return NULL; // PATH is not set
	}

	char *path_copy = ft_strdup(path); // Duplicate PATH to avoid modifying the original
	if (!path_copy) {
		perror("strdup");
	return NULL;
	}

	char *dir = strtok(path_copy, ":"); // Tokenize PATH
	while (dir)
	{
		char full_path[256];
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return strdup(full_path);
		}
		dir = strtok(NULL, ":");
    }

	free(path_copy);
	return NULL; // Command not found
}

int execute_external_command(t_command *cmd, char ***envp)
{
    char *binary_path;
    pid_t pid;
    int status;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (1); // Comando vacío

    binary_path = find_binary_in_path(cmd->args[0]);
    if (!binary_path)
    {
        fprintf(stderr, "minishell: command not found: %s\n", cmd->args[0]);
        return (127); // Código de error para comando no encontrado
    }

    pid = fork();
    if (pid == 0) // Proceso hijo
    {
        if (execve(binary_path, cmd->args, *envp) == -1)
        {
            perror("execve");
            exit(1);
        }
    }
    else if (pid > 0) // Proceso padre
    {
        waitpid(pid, &status, 0);
        free(binary_path);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status)); // Código de salida del hijo
    }
    else
    {
        perror("fork");
        free(binary_path);
        return (1);
    }

    return (0);
}
