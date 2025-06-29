/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:50 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 02:53:22 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Función para validar si un nombre de variable es válido
int is_valid_identifier(const char *name)
{
    if (!name || !*name)
        return (0);
    
    // Primer carácter debe ser letra o underscore
    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    
    // Resto de caracteres deben ser alfanuméricos o underscore
    for (int i = 1; name[i]; i++)
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
    }
    
    return (1);
}

int builtin_export(char **args, char ***env)
{
    int i = 1;
    
    // Si no hay argumentos, mostrar todas las variables exportadas
    if (!args[1])
    {
        char **current = *env;
        while (*current)
        {
            char *equal_sign = strchr(*current, '=');
            if (equal_sign)
            {
                // Separar nombre y valor
                int name_len = equal_sign - *current;
                char *name = ft_substr(*current, 0, name_len);
                char *value = equal_sign + 1;
                
                printf("declare -x %s=\"%s\"\n", name, value);
                free(name);
            }
            else
            {
                // Variable sin valor
                printf("declare -x %s\n", *current);
            }
            current++;
        }
        return (0);
    }
    
    // Procesar cada argumento
    while (args[i])
    {
        char *arg = args[i];
        char *equal_sign = strchr(arg, '=');
        char *var_name;
        
        if (equal_sign)
        {
            // Formato: VAR=valor
            int name_len = equal_sign - arg;
            var_name = ft_substr(arg, 0, name_len);
        }
        else
        {
            // Formato: VAR (sin valor)
            var_name = ft_strdup(arg);
        }
        
        // Validar el nombre de la variable
        if (!is_valid_identifier(var_name))
        {
            char *prefix = "export: ";
            char *suffix = ": not a valid identifier";
            
            char *part1 = ft_strjoin(prefix, arg);
            char *full_msg = ft_strjoin(part1, suffix);
            
            write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
            write(STDERR_FILENO, "\n", 1);
            
            free(part1);
            free(full_msg);
            free(var_name);
            return (1);
        }
        
        // Si llegamos aquí, el identificador es válido
        if (equal_sign)
        {
            // Establecer la variable con su valor
            char *var_value = equal_sign + 1;
            setenv(var_name, var_value, 1);
        }
        else
        {
            // Solo exportar la variable (sin cambiar su valor)
            char *existing_value = getenv(var_name);
            if (existing_value)
                setenv(var_name, existing_value, 1);
            // Si no existe, no hacer nada (comportamiento de bash)
        }
        
        free(var_name);
        i++;
    }
    
    return (0);  // Éxito
}
