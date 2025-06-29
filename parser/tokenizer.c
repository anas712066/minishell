/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:06:14 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 15:42:14 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/tokenizer.h"



// Función para extraer una palabra con manejo de comillas
char *extract_word_with_quotes(char *line, int *i)
{
    char *raw_content = malloc(1024);
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    int should_expand = 0;
    int was_in_single_quote = 0;  // ← NUEVA VARIABLE
    
    // Extraer contenido, removiendo comillas
    while (line[*i] && (in_single_quote || in_double_quote || 
           (line[*i] != ' ' && line[*i] != '\t' && 
            line[*i] != '|' && line[*i] != '<' && line[*i] != '>')))
    {
        if (line[*i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            was_in_single_quote = 1;  // ← MARCAR QUE ESTUVO EN COMILLAS SIMPLES
            (*i)++;
            continue;
        }
        if (line[*i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            should_expand = 1;  // Expandir en comillas dobles
            (*i)++;
            continue;
        }
        raw_content[j++] = line[(*i)++];
    }
    raw_content[j] = '\0';
    if (was_in_single_quote)   // NO expandir si estuvo en comillas simples
    {
        return raw_content;
    }
    // SÍ expandir si NO estuvo en comillas simples
    char *expanded = expand_variables(raw_content);
    free(raw_content);
    return expanded;
}

// Función para crear un nuevo token
t_token *create_token(char *value, t_token_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    
    token->value = value;
    token->type = type;
    token->next = NULL;
    return token;
}



// Función principal de tokenización
t_token *tokenize(char *line)
{
    t_token *tokens = NULL;
    t_token *new_token;
    int i = 0;
    
    while (line[i])
    {
        handle_spaces(line, &i);
        if (!line[i])
            break;
        
        new_token = process_token(line, &i);
        if (new_token)
            add_token(&tokens, new_token);
    }
    
    return tokens;
}

// Función para liberar tokens
void free_tokens(t_token *tokens)
{
    t_token *tmp;
    
    while (tokens)
    {
        tmp = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}