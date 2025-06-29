/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:46:23 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 17:09:11 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/parser.h"

static char	*process_variable_expansion(const char *line, int *i, char *result)
{
	char	*temp;
	char	*expanded;

	temp = expand_variable(line, i);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	expanded = join_and_free(result, temp);
	return (expanded);
}

static char	*process_literal_text(const char *line, int *i, char *result)
{
	char	*temp;
	char	*expanded;

	temp = extract_literal_part(line, i);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	expanded = join_and_free(result, temp);
	return (expanded);
}

static char	*expand_line_loop(const char *line, char *result)
{
	int	i;

	i = 0;
	while (line[i])
	{
		result = process_literal_text(line, &i, result);
		if (!result)
			return (NULL);
		if (line[i] == '$')
		{
			result = process_variable_expansion(line, &i, result);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

char	*expand_line(const char *line)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (expand_line_loop(line, result));
}
