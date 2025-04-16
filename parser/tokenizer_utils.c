/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:24:03 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/16 17:47:15 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../include/tokenizer.h"

void	handle_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token_type	get_type(const char *str, int *len)
{
	if (!strncmp(str, "<<", 2))
		return (*len = 2, T_HEREDOC);
	if (!strncmp(str, ">>", 2))
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

t_token	*process_token(char *line, int *i)
{
	t_token			*new;
	int				len;
	t_token_type	type;
	char			*value;

	type = get_type(&line[*i], &len);
	if (len > 0)
	{
		value = ft_strndup(&line[*i], len);
		*i += len;
	}
	else
		value = extract_word(line, i);
	new = new_token(value, type);
	free(value);
	return (new);
}
