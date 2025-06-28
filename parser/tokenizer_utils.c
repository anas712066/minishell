/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:24:03 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/28 23:16:59 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../include/tokenizer.h"

// Función para manejar espacios en blanco
void handle_spaces(char *line, int *i)
{
    while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
        (*i)++;
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token_type	get_type(const char *str, int *len)
{
	if (!ft_strncmp(str, "<<", 2))
		return (*len = 2, T_HEREDOC);
	if (!ft_strncmp(str, ">>", 2))
		return (*len = 2, T_APPEND);
	if (str[0] == '<')
		return (*len = 1, T_REDIR_IN);
	if (str[0] == '>')
		return (*len = 1, T_REDIR_OUT);
	if (str[0] == '|')
		return (*len = 1, T_PIPE);
	*len = 0;
	return (T_WORD);
}

// Función para procesar un token
t_token *process_token(char *line, int *i)
{
    char *value;
    
    // Manejo de operadores especiales
    if (line[*i] == '|')
    {
        if (line[*i + 1] == '|')
        {
            (*i) += 2;
            return create_token(ft_strdup("||"), T_LOGICAL_OR);
        }
        (*i)++;
        return create_token(ft_strdup("|"), T_PIPE);
    }
    
    if (line[*i] == '&' && line[*i + 1] == '&')
    {
        (*i) += 2;
        return create_token(ft_strdup("&&"), T_LOGICAL_AND);
    }
    
    if (line[*i] == '<')
    {
        if (line[*i + 1] == '<')
        {
            (*i) += 2;
            return create_token(ft_strdup("<<"), T_HEREDOC);
        }
        (*i)++;
        return create_token(ft_strdup("<"), T_REDIR_IN);
    }
    
    if (line[*i] == '>')
    {
        if (line[*i + 1] == '>')
        {
            (*i) += 2;
            return create_token(ft_strdup(">>"), T_APPEND);
        }
        (*i)++;
        return create_token(ft_strdup(">"), T_REDIR_OUT);
    }
    
    // Para palabras (incluyendo las que tienen comillas)
    value = extract_word_with_quotes(line, i);
    if (!value)
        return NULL;
    
    return create_token(value, T_WORD);
}
