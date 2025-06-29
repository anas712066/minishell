/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:06:14 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 16:47:06 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

void	handle_single_quote(int *i, int *in_single_quote,
		int *was_in_single_quote)
{
	*in_single_quote = !(*in_single_quote);
	*was_in_single_quote = 1;
	(*i)++;
}

void	handle_double_quote(int *i, int *in_double_quote)
{
	*in_double_quote = !(*in_double_quote);
	(*i)++;
}

char	*process_extraction(char *raw_content, int was_in_single_quote)
{
	char	*expanded;

	if (was_in_single_quote)
		return (raw_content);
	expanded = expand_variables(raw_content);
	free(raw_content);
	return (expanded);
}

char	*extract_word_with_quotes(char *line, int *i)
{
	char	*raw_content;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	int		was_in_single_quote;

	raw_content = malloc(1024);
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	was_in_single_quote = 0;
	while (line[*i] && (in_single_quote || in_double_quote
			|| !is_delimiter(line[*i])))
	{
		if (line[*i] == '\'' && !in_double_quote)
			handle_single_quote(i, &in_single_quote,
				&was_in_single_quote);
		else if (line[*i] == '"' && !in_single_quote)
			handle_double_quote(i, &in_double_quote);
		else
			raw_content[j++] = line[(*i)++];
	}
	raw_content[j] = '\0';
	return (process_extraction(raw_content, was_in_single_quote));
}

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	t_token	*new_token;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		handle_spaces(line, &i);
		if (!line[i])
			break ;
		new_token = process_token(line, &i);
		if (new_token)
			add_token(&tokens, new_token);
	}
	return (tokens);
}
