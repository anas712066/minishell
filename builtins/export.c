/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:50 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/28 21:03:04 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
        // Mostrar variables (implementar según necesites)
        char **current = *env;
        while (*current)
        {
            printf("declare -x %s\n", *current);
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
            fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
            free(var_name);
            return (1);  // Error
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
