/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:13:11 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/16 21:24:07 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>

void	handle_quote_error(int quote_type)
{
	if (quote_type == 1)
		fprintf(stderr, "Error: Comillas simples no cerradas.\n");
	else if (quote_type == 2)
		fprintf(stderr, "Error: Comillas dobles no cerradas.\n");
	else if (quote_type == 3)
		fprintf(stderr, "Error: Comillas no emparejadas correctamente.\n");
}

void	handle_empty_token_error(const char *token)
{
	if (token == NULL || token[0] == '\0')
	{
		fprintf(stderr, "Error: Token vacío detectado.\n");
		return (1);
	}
	return (0);
}
