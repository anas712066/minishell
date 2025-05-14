/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:20 by mumajeed          #+#    #+#             */
/*   Updated: 2025/05/14 13:45:40 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../include/exec.h"

int handle_redirections(t_command *cmd)
{
    int fd;

    if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd < 0)
        {
            perror("minishell");
            return (1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    if (cmd->outfile)
    {
        int flags = O_WRONLY | O_CREAT | (cmd->append ? O_APPEND : O_TRUNC);
        fd = open(cmd->outfile, flags, 0644);
        if (fd < 0)
        {
            perror("minishell");
            return (1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return (0);
}
