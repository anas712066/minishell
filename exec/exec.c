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

char *find_binary_in_path(const char *command) {
    char *path = getenv("PATH");
    if (path) {
        char *dir = strtok(path, ":");
        while (dir) {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
            if (access(full_path, X_OK) == 0) {
                return strdup(full_path);
            }
            dir = strtok(NULL, ":");
        }
    }
    return NULL;  // Si no se encuentra el comando
}