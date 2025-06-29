#include "syntax_validation.h"
#include "error_handler.h"
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int validate_syntax(t_token *tokens)
{
    t_token *current = tokens;

    while (current)
    {
        // Verificar redirecciones
        if (current->type == T_REDIR_OUT || current->type == T_APPEND ||
            current->type == T_REDIR_IN || current->type == T_HEREDOC)
        {
            // Redirección sin un siguiente token que sea un T_WORD
            if (!current->next)
            {
                // Si no hay siguiente token → newline
                write(STDERR_FILENO, " syntax error near unexpected token `newline'\n", 46);
                return (0);
            }
            else if (current->next->type != T_WORD)
            {
                // Si hay siguiente token pero no es WORD → mostrar ese token
                if (current->next->type == T_PIPE)
                    write(STDERR_FILENO, " syntax error near unexpected token `|'\n", 40);
                else if (current->next->type == T_REDIR_OUT)
                    write(STDERR_FILENO, " syntax error near unexpected token `>'\n", 40);
                else if (current->next->type == T_APPEND)
                    write(STDERR_FILENO, " syntax error near unexpected token `>>'\n", 41);
                else if (current->next->type == T_REDIR_IN)
                    write(STDERR_FILENO, " syntax error near unexpected token `<'\n", 40);
                else if (current->next->type == T_HEREDOC)
                    write(STDERR_FILENO, " syntax error near unexpected token `<<'\n", 41);
                else
                    write(STDERR_FILENO, " syntax error near unexpected token `newline'\n", 47);
                return (0);
            }
        }

        // Verificar pipes mal colocados
        if (current->type == T_PIPE)
        {
            // Pipe al principio, al final o seguido de otro pipe
            if (current == tokens || !current->next)
            {
                write(STDERR_FILENO, " syntax error near unexpected token `|'\n", 40);
                return (0);
            }
            // Pipes consecutivos
            else if (current->next->type == T_PIPE)
            {
                write(STDERR_FILENO, " syntax error near unexpected token `|'\n", 40);
                return (0);
            }
        }

        // Comprobar comillas no emparejadas o mal usadas
        if (current->value && (current->value[0] == '"' || current->value[0] == '\''))
        {
            if (!check_quotes(current->value)) // Verifica si las comillas están emparejadas
            {
                return (0);
            }
        }

        current = current->next;
    }

    return (1); // Sintaxis válida
}

int execute_command(t_token *tokens) {
    pid_t pid;
    int status;
    char *argv[] = {tokens->value, NULL};  // El primer token es el comando, como "ls"
    char *path = "/bin/";  // Ruta del directorio donde se encuentran los comandos (para simplificar)
    char full_path[256];   // Aquí almacenamos la ruta completa del ejecutable

    // Concatenar la ruta y el comando (por ejemplo, "/bin/ls")
    printf(full_path, sizeof(full_path), "%s%s", path, tokens->value);

    pid = fork();
    if (pid == 0) {
        // Proceso hijo
        if (execve(full_path, argv, NULL) == -1) {
            perror("execve failed");
            exit(1);  // Salir con error si el comando no se puede ejecutar
        }
    } else if (pid > 0) {
        // Proceso padre
        wait(&status);  // Espera a que el hijo termine
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);  // Devuelve el código de salida del comando
        }
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;  // Deberías manejar este caso también
}

// Función para verificar y validar operadores lógicos y pipes
int handle_logical_operator(t_token *tokens)
{
    t_token *current = tokens;
    
    while (current)
    {
        if (current->type == T_PIPE)
        {
            // Verificar que hay comandos antes y después del pipe
            if (!current->next || current->next->type != T_WORD)
            {
                write(STDERR_FILENO, " syntax error near unexpected token `|'\n", 39);
                return (0); // Error de sintaxis
            }
        }/*
        else if (current->type == T_LOGICAL_AND)
        {
            // Verificar que hay comandos antes y después de &&
            if (!current->next || current->next->type != T_WORD)
            {
                printf("minishell: syntax error near unexpected token `&&'\n");
                return (0); // Error de sintaxis
            }
        }
        else if (current->type == T_LOGICAL_OR)
        {
            // Verificar que hay comandos antes y después de ||
            if (!current->next || current->next->type != T_WORD)
            {
                printf("minishell: syntax error near unexpected token `||'\n");
                return (0); // Error de sintaxis
            }
        }
        
        */
        
        current = current->next;
    }
    
    return (1); // Todo correcto
}

int validate_command_exists(const char *command)
{
    if (access(command, F_OK) == -1)
    {
        handle_command_not_found_error();  // Comando no encontrado
        return (0);
    }
    return (1);  // El comando existe
}

