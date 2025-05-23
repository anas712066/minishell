/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:16:38 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/16 21:06:06 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>

int	check_quotes(const char *line)
{
	int	i;
	int	quote_count_single;
	int	quote_count_double;

	i = 0;
	quote_count_single = 0;
	quote_count_double = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			quote_count_double++;
		else if (line[i] == '\'')
			quote_count_single++;
		i++;
	}
	if (quote_count_single % 2 || quote_count_double % 2)
	{
		handle_quote_error((quote_count_single % 2) + 2
			* (quote_count_double % 2));
		return (0);
	}
	return (1);
}
