/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:18 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/28 22:09:09 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/exec.h"

int execute_pipeline(t_command *cmd, char ***envp)
{
    int pipefd[2];
    pid_t pid1, pid2;
    int status1, status2;
    
    if (!cmd || !cmd->next)
    {
        // Comando único (sin pipe)
        if (cmd && cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
            return execute_builtin(cmd, envp);
        else if (cmd)
            return execute_external_command(cmd, envp);
        return 0;
    }
    
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (1);
    }
    
    // PRIMER PROCESO HIJO - Comando izquierdo (escritor)
    pid1 = fork();
    if (pid1 == 0)
    {
        close(pipefd[0]);                    // Cerrar lectura
        dup2(pipefd[1], STDOUT_FILENO);      // Redirigir stdout al pipe
        close(pipefd[1]);
        
        // Ejecutar primer comando
        if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
            exit(execute_builtin(cmd, envp));
        else
            exit(execute_external_command(cmd, envp));
    }
    
    // SEGUNDO PROCESO HIJO - Comando derecho (lector)
    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipefd[1]);                    // Cerrar escritura
        dup2(pipefd[0], STDIN_FILENO);       // Redirigir stdin del pipe
        close(pipefd[0]);
        
        // Si hay más comandos en la pipeline, continuar recursivamente
        if (cmd->next->pipe)
            exit(execute_pipeline(cmd->next, envp));
        else
        {
            // Último comando de la pipeline
            if (cmd->next->args && cmd->next->args[0] && is_builtin(cmd->next->args[0]))
                exit(execute_builtin(cmd->next, envp));
            else
                exit(execute_external_command(cmd->next, envp));
        }
    }
    
    // PROCESO PADRE - Cerrar pipes y esperar
    close(pipefd[0]);
    close(pipefd[1]);
    
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    
    // Retornar exit code del último comando
    if (WIFEXITED(status2))
        return WEXITSTATUS(status2);
    return 1;
}