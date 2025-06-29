/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:48 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 02:31:42 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

// Función para verificar si una cadena es un número válido Y detectar overflow
int is_numeric_with_overflow_check(const char *str, long *result)
{
    if (!str || !*str)
        return (0);
    
    char *endptr;
    errno = 0;  // Resetear errno antes de strtol
    
    *result = strtol(str, &endptr, 10);
    
    // Verificar overflow/underflow
    if (errno == ERANGE)
        return (-1);  // -1 indica overflow
    
    // Verificar que se parseó todo el string
    if (*endptr != '\0')
        return (0);   // 0 indica formato inválido
    
    return (1);       // 1 indica éxito
}

int builtin_exit(char **args)
{
    int arg_count = 0;
    long exit_code_long = 0;
    
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
        int check_result = is_numeric_with_overflow_check(args[1], &exit_code_long);
        
        if (check_result == -1)
        {
            // Overflow detectado
            write(STDERR_FILENO, "minishell: exit: ", 17);
            write(STDERR_FILENO, args[1], strlen(args[1]));
            write(STDERR_FILENO, ": numeric argument required\n", 28);
            exit(2);
        }
        else if (check_result == 0)
        {
            // Formato inválido
            handle_exit_numeric_argument_error(args[1]);
            exit(2);
        }
        
        // Número válido, usar solo los 8 bits menos significativos
        exit(exit_code_long & 255);
    }
    else
    {
        // exit con múltiples argumentos → error
        long dummy;
        int check_result = is_numeric_with_overflow_check(args[1], &dummy);
        
        if (check_result == -1)
        {
            // Overflow en el primer argumento
            write(STDERR_FILENO, "minishell: exit: ", 17);
            write(STDERR_FILENO, args[1], strlen(args[1]));
            write(STDERR_FILENO, ": numeric argument required\n", 28);
            exit(2);
        }
        else if (check_result == 0)
        {
            // Formato inválido en el primer argumento
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