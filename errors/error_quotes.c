/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:16:38 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/28 16:19:26 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>

int	check_quotes(const char *line)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
		}
		else if (line[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
		}
		i++;
	}
	if (in_single_quote)
	{
		printf("Error: Comillas simples no cerradas.\n");
		return (0);
	}
	if (in_double_quote)
	{
		printf("Error: Comillas dobles no cerradas.\n");
		return (0);
	}
	return (1);
}
