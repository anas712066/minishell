/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:54:42 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 01:42:03 by mmilitar         ###   ########.fr       */
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

#include "../include/builtins.h"
#include "../include/minishell.h"
#include "../include/parser.h"

int	execute_builtin(t_command *cmd, char ***env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (strcmp(cmd->args[0], "cat") == 0 && !cmd->args[1])
	{
		printf("minishell: cat: waiting for input (Ctrl+D to exit)\n");
	}
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

	return (0); // No es un builtin, ejecutar como externo
}

// Función corregida para buscar binarios en PATH
char *find_binary_in_path(const char *command)
{
    // Si el comando ya es una ruta absoluta o relativa, verificarla directamente
    if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
    {
        if (access(command, X_OK) == 0)
            return ft_strdup(command);
        else
            return NULL; // El archivo no existe o no es ejecutable
    }
    
    // Si no es una ruta, buscar en PATH
    char *path = getenv("PATH");
    if (!path)
        return NULL;

    char *path_copy = ft_strdup(path);
    if (!path_copy)
    {
        perror("strdup");
        return NULL;
    }

    char *dir = strtok(path_copy, ":");
    while (dir)
    {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
        
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return ft_strdup(full_path);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

// Función corregida para ejecutar comandos externos
int execute_external_command(t_command *cmd, char ***envp)
{
    char *binary_path;
    pid_t pid;
    int status;
    struct stat st;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (1);

    // Manejar comando vacío - hacer shift de argumentos
    if (cmd->args[0][0] == '\0')
    {
        // Hacer shift: mover todos los argumentos una posición hacia la izquierda
        int i = 0;
        while (cmd->args[i + 1])
        {
            cmd->args[i] = cmd->args[i + 1];
            i++;
        }
        cmd->args[i] = NULL;
        
        // Si después del shift no hay argumentos, return 0
        if (!cmd->args[0])
            return (0);
    }

    // Si el comando empieza con ./ o es una ruta absoluta, verificar directamente
    if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
    {
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
        binary_path = ft_strdup(cmd->args[0]);
    }
    else
    {
        // Para comandos sin ./ o ruta absoluta, buscar en PATH primero
        binary_path = find_binary_in_path(cmd->args[0]);
        if (!binary_path)
        {
            // Si no se encuentra en PATH, verificar si es archivo local
            if (stat(cmd->args[0], &st) == 0)
            {
                if (S_ISDIR(st.st_mode))
                {
                    write(STDERR_FILENO, "minishell: command not found: ", 30);
                    write(STDERR_FILENO, cmd->args[0], strlen(cmd->args[0]));
                    write(STDERR_FILENO, "\n", 1);
                    return (127);  // Para directorios sin ./ -> command not found
                }
                if (access(cmd->args[0], X_OK) != 0)
                {
                    write(STDERR_FILENO, "minishell: command not found: ", 30);
                    write(STDERR_FILENO, cmd->args[0], strlen(cmd->args[0]));
                    write(STDERR_FILENO, "\n", 1);
                    return (127);  // Para archivos sin permisos sin ./ -> command not found
                }
                // Si existe y es ejecutable, usar la ruta directa
                binary_path = ft_strdup(cmd->args[0]);
            }
            else
            {
                // Si no existe ni en PATH ni como archivo local
                write(STDERR_FILENO, "minishell: command not found: ", 30);
                write(STDERR_FILENO, cmd->args[0], strlen(cmd->args[0]));
                write(STDERR_FILENO, "\n", 1);
                return (127);
            }
        }
    }

    pid = fork();
    if (pid == 0) // Proceso hijo
    {
        // Aplicar redirecciones usando la nueva función
        if (handle_redirections(cmd) != 0)
        {
            free(binary_path);
            exit(1);
        }
        
        // DESPUÉS ejecutar el comando
        if (execve(binary_path, cmd->args, *envp) == -1)
        {
            perror("execve failed");
            free(binary_path);
            exit(1);
        }
    }
    else if (pid > 0) // Proceso padre
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