/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:41:48 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 16:23:20 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

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

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
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

void	handle_spaces(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
