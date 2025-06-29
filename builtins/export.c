/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:50 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 19:37:31 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	builtin_export(char **args, char ***env)
{
	int	i;

	if (!args[1])
		return (print_all_exported_vars(env));
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env) != 0)
			return (1);
		i++;
	}
	return (0);
}

char **add_var_to_env(char **env, char *var_name, char *var_value)
{
    int count = 0;
    int i;
    
    // Contar variables existentes
    while (env[count]) 
        count++;
    
    // Verificar si la variable ya existe (para actualizarla)
    for (i = 0; i < count; i++)
    {
        char *equal_sign = strchr(env[i], '=');
        if (equal_sign)
        {
            size_t name_len = equal_sign - env[i];
            if (ft_strncmp(env[i], var_name, name_len) == 0 && name_len == ft_strlen(var_name))
            {
                // Variable existe, actualizarla
                free(env[i]);
                char *temp = ft_strjoin(var_name, "=");
                env[i] = ft_strjoin(temp, var_value);
                free(temp);
                return env;
            }
        }
    }
    
    // Variable nueva, expandir array
    char **new_env = malloc(sizeof(char *) * (count + 2));
    if (!new_env)
        return env;
    
    // Copiar variables existentes
    for (i = 0; i < count; i++)
        new_env[i] = env[i];
    
    // Agregar nueva variable
    char *temp = ft_strjoin(var_name, "=");
    new_env[count] = ft_strjoin(temp, var_value);
    new_env[count + 1] = NULL;
    free(temp);
    
    return new_env;
}