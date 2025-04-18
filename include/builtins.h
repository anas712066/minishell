#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/minishell.h"

int builtin_echo(char **args);
int builtin_cd(char **args);
int builtin_pwd(void);
int builtin_export(char **args, char ***env);
int builtin_unset(char **args, char ***env);
int builtin_env(char **env);
int builtin_exit(char **args);

int is_builtin(const char *cmd);
int execute_builtin(t_command *cmd, char ***env);

#endif
