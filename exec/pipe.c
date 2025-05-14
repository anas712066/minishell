/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:18 by mumajeed          #+#    #+#             */
/*   Updated: 2025/05/14 13:45:59 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/exec.h"

int execute_pipeline(t_command *cmd, char ***envp)
{
    int pipefd[2];
    pid_t pid;
    int status;

    if (!cmd || !cmd->next)
        return execute_external_command(cmd, envp);

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (1);
    }

    pid = fork();
    if (pid == 0) // Proceso hijo
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exit(execute_external_command(cmd, envp));
    }
    else if (pid > 0) // Proceso padre
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        waitpid(pid, &status, 0);
        return execute_pipeline(cmd->next, envp);
    }
    else
    {
        perror("fork");
        return (1);
    }
}
