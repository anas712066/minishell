/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:48 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 00:02:54 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Función para verificar si una cadena es un número válido
int is_numeric(const char *str)
{
    if (!str || !*str)
        return (0);
    
    int i = 0;
    
    // Permitir signo opcional al inicio
    if (str[i] == '+' || str[i] == '-')
        i++;
    
    // Debe tener al menos un dígito después del signo (si lo hay)
    if (!str[i])
        return (0);
    
    // Verificar que el resto sean dígitos
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    
    return (1);
}

int builtin_exit(char **args)
{
    int arg_count = 0;
    int exit_code = 0;
    
    // Contar argumentos (sin incluir "exit")
    while (args[arg_count + 1])
        arg_count++;
    
    printf("exit\n");  // bash siempre imprime "exit"
    
    if (arg_count == 0)
    {
        // exit sin argumentos → usar el último exit code
        exit(g_last_status);
    }
    else if (arg_count == 1)
    {
        // exit con un argumento → debe ser numérico
        if (!is_numeric(args[1]))
        {
            handle_exit_numeric_argument_error(args[1]);
            exit(2);  // Exit code específico para argumento no numérico
        }
        
        exit_code = ft_atoi(args[1]);
        exit(exit_code & 255);  // bash usa solo los 8 bits menos significativos
    }
    else
    {
        // exit con múltiples argumentos → error
        if (!is_numeric(args[1]))
        {
            // Si el primer argumento no es numérico, es error de argumento numérico
            handle_exit_numeric_argument_error(args[1]);
            exit(2);
        }
        else
        {
            // Si el primer argumento es numérico pero hay más argumentos
            handle_exit_too_many_args_error();
            return (1);  // NO hacer exit(), solo retornar error
        }
    }
    
    return (0);  // Esta línea nunca debería ejecutarse
}
