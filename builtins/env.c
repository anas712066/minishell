/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:43 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 19:24:32 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int builtin_env(char **envp)
{
    int i = 0;
    
    while (envp[i])
    {
        char *equal_sign = strchr(envp[i], '=');
        if (equal_sign)
        {
            // Extraer nombre de variable
            int name_len = equal_sign - envp[i];
            char *var_name = ft_substr(envp[i], 0, name_len);
            
            // Obtener valor actual con getenv()
            char *current_value = getenv(var_name);
            if (current_value)
                printf("%s=%s\n", var_name, current_value);
            
            free(var_name);
        }
        else
        {
            // Variable sin valor, verificar si aún existe
            char *current_value = getenv(envp[i]);
            if (current_value)
                printf("%s=%s\n", envp[i], current_value);
        }
        i++;
    }
    
    return (0);
}