/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:57 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 19:46:40 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../libft/libft.h"

int	builtin_unset(char **args, char ***env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unsetenv(args[i]);
		*env = remove_var_from_env(*env, args[i]);
		i++;
	}
	return (0);
}

char **remove_var_from_env(char **env, char *var_name)
{
    int count = 0;
    int i, j;
    
    // Contar variables existentes
    while (env[count]) 
        count++;
    
    // Buscar la variable a eliminar
    for (i = 0; i < count; i++)
    {
        char *equal_sign = strchr(env[i], '=');
        if (equal_sign)
        {
            size_t name_len = equal_sign - env[i];
            if (ft_strncmp(env[i], var_name, name_len) == 0 && name_len == ft_strlen(var_name))
            {
                // Variable encontrada, eliminarla
                
                // Mover todas las variables siguientes una posición hacia atrás
                for (j = i; j < count - 1; j++)
                    env[j] = env[j + 1];
                    
                env[count - 1] = NULL;
                return env;
            }
        }
        else
        {
            // Variable sin valor
            if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0 && ft_strlen(env[i]) == ft_strlen(var_name))
            {
                
                // Mover todas las variables siguientes una posición hacia atrás
                for (j = i; j < count - 1; j++)
                    env[j] = env[j + 1];
                    
                env[count - 1] = NULL;
                return env;
            }
        }
    }
    
    return env;  // Variable no encontrada
}