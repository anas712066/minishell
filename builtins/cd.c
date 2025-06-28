/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:40 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/28 20:52:58 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int builtin_cd(char **args)
{
    char *path;
    int arg_count = 0;
    
    // Contar argumentos (sin incluir "cd")
    while (args[arg_count + 1])
        arg_count++;
    
    // Validar número de argumentos
    if (arg_count > 1)
    {
        fprintf(stderr, "cd: too many arguments\n");
        return (1);  // Error
    }
    
    // Determinar el directorio destino
    if (arg_count == 0)
    {
        // cd sin argumentos → ir a HOME
        path = getenv("HOME");
        if (!path)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return (1);
        }
    }
    else
    {
        // cd con un argumento
        path = args[1];
    }
    
    // Intentar cambiar directorio
    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);  // Error
    }
    
    return (0);  // Éxito
}