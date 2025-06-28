/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:41:48 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/28 17:29:23 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"
#include <stdlib.h>

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}


// Función para agregar un token a la lista
void add_token(t_token **tokens, t_token *new_token)
{
    t_token *current;
    
    if (!new_token)
        return;
    
    if (!*tokens)
    {
        *tokens = new_token;
        return;
    }
    
    current = *tokens;
    while (current->next)
        current = current->next;
    
    current->next = new_token;
}

char	*extract_word(const char *line, int *i)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[(*i)++];
		while (line[*i] && line[*i] != quote)
			(*i)++;
		(*i)++;
	}
	else
	{
		while (line[*i] && line[*i] != ' ' && !is_special_char(line[*i]))
			(*i)++;
	}
	return (ft_strndup(line + start, *i - start));
}
