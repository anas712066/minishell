/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:46:23 by mumajeed          #+#    #+#             */
/*   Updated: 2025/04/16 22:12:19 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"
#include "libft.h"
#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/error_handler.h"


int g_exit_status = 0;

char	*expand_variable(const char *line, int *i)
{
	int		start;
	char	*var_name;
	char	*value;

	start = ++(*i); //Saltar el símbolo '$'
	if (line[start] == '?') // Manejar $?
	{
		(*i)++;
		return (ft_itoa(g_exit_status)); // Convertir g_exit_status a string
	}
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(line + start, *i - start);
	value = getenv(var_name); // Obtener el valor de la variable de entorno
	free(var_name);
	return (value ? ft_strdup(value) : ft_strdup("")); // Retornar valor o cadena vacía
}

char	*expand_line(const char *line)
{
	char	*result;
	char	*temp;
	char	*expanded;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		start = i;
		while (line[i] && line[i] != '$')
			i++;
		temp = ft_strndup(line + start, i - start); // Copiar texto antes de '$'
		expanded = ft_strjoin(result, temp); // Concatenar al resultado
		free(result);
		free(temp);
		result = expanded;
		if (line[i] == '$') // Expandir variable
		{
			temp = expand_variable(line, &i);
			expanded = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = expanded;
		}
	}
	return (result);
}
