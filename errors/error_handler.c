/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:13:11 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/16 19:14:20 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>

void	handle_quote_error(int quote_status)
{
	if (quote_status == 1)
	{
		printf("Error: Comillas no cerradas.\n");
	}
}

void	handle_empty_token_error(const char *token)
{
	if (token == NULL || token[0] == '\0')
	{
		printf("Error: Token vacío detectado.\n");
	}
}
