/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:24:18 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 16:51:33 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

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

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}
