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
            if (!current->next || current->next->type != T_WORD)
            {
                fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
                return (0);
            }
        }

        // Verificar pipes mal colocados
        if (current->type == T_PIPE)
        {
            // Pipe al principio, al final o seguido de otro pipe
            if (current == tokens || !current->next || current->next->type == T_PIPE)
            {
                fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
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
    snprintf(full_path, sizeof(full_path), "%s%s", path, tokens->value);

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

int handle_logical_operator(t_token *tokens)
{
    int status = 0;

    while (tokens)
    {
        if (tokens->type == T_WORD)
        {
            status = execute_command(tokens); // Pasa el token completo
        }
        else if (tokens->type == T_LOGICAL_AND && status == 0)
        {
            tokens = tokens->next; // Ejecuta el siguiente comando si el anterior tuvo éxito
        }
        else if (tokens->type == T_LOGICAL_OR && status != 0)
        {
            tokens = tokens->next; // Ejecuta el siguiente comando si el anterior falló
        }
        tokens = tokens->next;
    }
    return status;
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

