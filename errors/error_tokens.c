/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:40:58 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 13:41:04 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error_handler.h"

void	validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (!current->value || current->value[0] == '\0')
			handle_empty_token_error(current->value);
		current = current->next;
	}
}

void	handle_empty_token_error(const char *token)
{
	if (token == NULL || token[0] == '\0')
	{
		printf("\n");
	}
}
