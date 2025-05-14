/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:46:23 by mumajeed          #+#    #+#             */
/*   Updated: 2025/05/14 14:12:18 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

int	g_exit_status = 0;

char	*expand_variable(const char *line, int *i)
{
    int		start;
    char	*var_name;
    char	*value;

    start = ++(*i); // Avanza después del '$'
    if (line[start] == '?') // Manejar $?
    {
        (*i)++;
        return (ft_itoa(g_exit_status)); // Devuelve el código de salida como string
    }
    while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
        (*i)++;
    var_name = ft_strndup(line + start, *i - start); // Extrae el nombre de la variable
    if (!var_name)
        return (NULL);
    value = getenv(var_name); // Obtiene el valor de la variable de entorno
    free(var_name);
    return (value ? ft_strdup(value) : ft_strdup("")); // Devuelve el valor o una cadena vacía
}

char	*expand_line(const char *line)
{
	char	*result;
	char	*temp;
	char	*expanded;
	int		i;
	int		start;

	result = ft_strdup("");
	if (!result) // Verifica si ft_strdup falló
		return (NULL);
	i = 0;
	while (line[i])
	{
		start = i;
		while (line[i] && line[i] != '$')
			i++;
		temp = ft_strndup(line + start, i - start);
		if (!temp)
        {
            free(result); // Libera la memoria asignada previamente
            return (NULL);
        }
		expanded = ft_strjoin(result, temp);
		free(result);
		free(temp);
		if (!expanded)
			return (NULL);
		result = expanded;
		if (line[i] == '$')
		{
			temp = expand_variable(line, &i);
			if (!temp)
			{
				free(result);
				return (NULL);
			}
			expanded = ft_strjoin(result, temp);
			free(result);
			free(temp);
			if (!expanded)
				return (NULL);
			result = expanded;
		}
	}
	return (result);
}
