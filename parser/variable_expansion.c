#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"
#include "../libft/libft.h"

char *expand_variables(char *str)
{
    if (!str)
        return NULL;
    
    char *result = malloc(2048);  // Buffer grande para expansiones
    if (!result)
        return NULL;
    
    int i = 0, j = 0;
    
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1])
        {
            if (str[i + 1] == '?')  // Caso especial: $?
            {
                char *exit_code_str = ft_itoa(g_last_exit_code);
                if (exit_code_str)
                {
                    int k = 0;
                    while (exit_code_str[k])
                        result[j++] = exit_code_str[k++];
                    free(exit_code_str);
                }
                i += 2;  // Saltar $?
            }
            else  // Variables normales: $USER, $HOME, etc.
            {
                int start = i + 1;
                int end = start;
                
                // Encontrar el final del nombre de variable
                while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
                    end++;
                
                if (end > start)  // Si hay nombre de variable
                {
                    char *var_name = ft_substr(str, start, end - start);
                    if (var_name)
                    {
                        char *var_value = getenv(var_name);
                        if (var_value)
                        {
                            int k = 0;
                            while (var_value[k])
                                result[j++] = var_value[k++];
                        }
                        free(var_name);
                    }
                    i = end;
                }
                else  // $ sin nombre válido
                {
                    result[j++] = str[i++];  // Copiar $ literal
                }
            }
        }
        else
        {
            result[j++] = str[i++];  // Copiar carácter normal
        }
    }
    
    result[j] = '\0';
    return result;
}