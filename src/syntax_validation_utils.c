/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:02:31 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 17:17:03 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_validation.h"

void	write_syntax_error(t_token_type type)
{
	if (type == T_PIPE)
		write(STDERR_FILENO, " syntax error near unexpected token `|'\n", 40);
	else if (type == T_REDIR_OUT)
		write(STDERR_FILENO, " syntax error near unexpected token `>'\n", 40);
	else if (type == T_APPEND)
		write(STDERR_FILENO, " syntax error near unexpected token `>>'\n", 41);
	else if (type == T_REDIR_IN)
		write(STDERR_FILENO, " syntax error near unexpected token `<'\n", 40);
	else if (type == T_HEREDOC)
		write(STDERR_FILENO, " syntax error near unexpected token `<<'\n", 41);
	else
		write(STDERR_FILENO,
			" syntax error near unexpected token `newline'\n", 47);
}

int	validate_next_token(t_token *current)
{
	if (current->next->type != T_WORD)
	{
		write_syntax_error(current->next->type);
		return (0);
	}
	return (1);
}

int	validate_redirection(t_token *current)
{
	if (!current->next)
	{
		write(STDERR_FILENO,
			" syntax error near unexpected token `newline'\n", 46);
		return (0);
	}
	return (validate_next_token(current));
}

int	handle_logical_operator(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (!current->next || current->next->type != T_WORD)
			{
				write(STDERR_FILENO,
					" syntax error near unexpected token `|'\n", 39);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	validate_command_exists(const char *command)
{
	if (access(command, F_OK) == -1)
	{
		handle_command_not_found_error();
		return (0);
	}
	return (1);
}
