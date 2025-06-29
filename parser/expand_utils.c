/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:14:58 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 16:16:06 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

char	*expand_variable(const char *line, int *i)
{
	int		start;
	char	*var_name;
	char	*value;

	start = ++(*i);
	if (line[start] == '?')
	{
		(*i)++;
		return (ft_itoa(g_last_status));
	}
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(line + start, *i - start);
	if (!var_name)
		return (NULL);
	value = getenv(var_name);
	free(var_name);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

char	*join_and_free(char *result, char *temp)
{
	char	*expanded;

	expanded = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (expanded);
}

char	*extract_literal_part(const char *line, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	while (line[*i] && line[*i] != '$')
		(*i)++;
	temp = ft_strndup(line + start, *i - start);
	return (temp);
}
