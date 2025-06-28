/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:20 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 01:37:53 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../include/exec.h"

int handle_redirections(t_command *cmd)
{
    t_redir *current;
    int fd;
    int last_infd = -1;
    int last_outfd = -1;

    if (!cmd || !cmd->redirs)
        return (0);

    current = cmd->redirs;
    while (current)
    {
        if (current->type == T_REDIR_IN)
        {
            // Cerrar fd anterior si existe
            if (last_infd != -1)
                close(last_infd);
                
            fd = open(current->filename, O_RDONLY);
            if (fd < 0)
            {
                perror("minishell");
                return (1);  // Error - falla todo el comando
            }
            last_infd = fd;
        }
        else if (current->type == T_REDIR_OUT)
        {
            // Cerrar fd anterior si existe
            if (last_outfd != -1)
                close(last_outfd);
                
            fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("minishell");
                return (1);
            }
            last_outfd = fd;
        }
        else if (current->type == T_APPEND)
        {
            // Cerrar fd anterior si existe
            if (last_outfd != -1)
                close(last_outfd);
                
            fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("minishell");
                return (1);
            }
            last_outfd = fd;
        }
        else if (current->type == T_HEREDOC)
        {
            // Cerrar fd anterior si existe
            if (last_infd != -1)
                close(last_infd);
                
            fd = open(current->filename, O_RDONLY);
            if (fd < 0)
            {
                perror("minishell");
                return (1);
            }
            last_infd = fd;
        }
        
        current = current->next;
    }
    
    // Aplicar las redirecciones finales
    if (last_infd != -1)
    {
        dup2(last_infd, STDIN_FILENO);
        close(last_infd);
    }
    if (last_outfd != -1)
    {
        dup2(last_outfd, STDOUT_FILENO);
        close(last_outfd);
    }
    
    return (0);
}