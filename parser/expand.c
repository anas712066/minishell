/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:46:23 by mumajeed          #+#    #+#             */
/*   Updated: 2025/04/16 22:32:23 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

int	g_exit_status = 0;

char	*expand_variable(const char *line, int *i)
{
	int		start;
	char	*var_name;
	char	*value;

	start = ++(*i);
	if (line[start] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(line + start, *i - start);
	value = getenv(var_name);
	free(var_name);
	return (value ? ft_strdup(value) : ft_strdup(""));
}

char	*expand_line(const char *line)
{
	char	*result;
	char	*temp;
	char	*expanded;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		start = i;
		while (line[i] && line[i] != '$')
			i++;
		temp = ft_strndup(line + start, i - start);
		expanded = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = expanded;
		if (line[i] == '$')
		{
			temp = expand_variable(line, &i);
			expanded = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = expanded;
		}
	}
	return (result);
}
