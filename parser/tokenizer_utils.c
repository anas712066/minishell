/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:24:03 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 16:49:59 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

static t_token	*handle_pipe_token(int *i)
{
	(*i)++;
	return (create_token(ft_strdup("|"), T_PIPE));
}

static t_token	*handle_input_redir(char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		(*i) += 2;
		return (create_token(ft_strdup("<<"), T_HEREDOC));
	}
	(*i)++;
	return (create_token(ft_strdup("<"), T_REDIR_IN));
}

static t_token	*handle_output_redir(char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		(*i) += 2;
		return (create_token(ft_strdup(">>"), T_APPEND));
	}
	(*i)++;
	return (create_token(ft_strdup(">"), T_REDIR_OUT));
}

static t_token	*handle_word_token(char *line, int *i)
{
	char	*value;

	value = extract_word_with_quotes(line, i);
	if (!value)
		return (NULL);
	return (create_token(value, T_WORD));
}

t_token	*process_token(char *line, int *i)
{
	if (line[*i] == '|')
		return (handle_pipe_token(i));
	if (line[*i] == '<')
		return (handle_input_redir(line, i));
	if (line[*i] == '>')
		return (handle_output_redir(line, i));
	return (handle_word_token(line, i));
}
