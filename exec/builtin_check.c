#include "../include/builtins.h"

int is_builtin(const char *cmd)
{
	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") || !strcmp(cmd, "pwd") ||
			!strcmp(cmd, "export") || !strcmp(cmd, "unset") ||
			!strcmp(cmd, "env") || !strcmp(cmd, "exit"));
}

int execute_builtin(t_command *cmd, char ***env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (!strcmp(cmd->args[0], "echo"))
		return builtin_echo(cmd->args);
	if (!strcmp(cmd->args[0], "cd"))
		return builtin_cd(cmd->args);

	// Agregar los demás aquí (cd, pwd, etc.)
	return (1);
}