/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:04:10 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/28 17:35:57 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/minishell.h"
#include "../include/parser.h"

int is_builtin(const char *cmd)
{
    if (!cmd)
        return (0);
    
    if (strcmp(cmd, "echo") == 0)
        return (1);
    if (strcmp(cmd, "cd") == 0)
        return (1);
    if (strcmp(cmd, "pwd") == 0)
        return (1);
    if (strcmp(cmd, "export") == 0)
        return (1);
    if (strcmp(cmd, "unset") == 0)
        return (1);
    if (strcmp(cmd, "env") == 0)
        return (1);
    if (strcmp(cmd, "exit") == 0)
        return (1);
    
    return (0);
}


