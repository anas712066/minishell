#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// Prototipos de funciones de ejecución
int execute_builtin(t_command *cmd, char ***env);
int execute_external_command(t_command *cmd, char ***envp);
char *find_binary_in_path(const char *command, char **envp);

#endif
