/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:16:38 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 20:22:00 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"

static int	process_quotes(const char *line, int *single, int *double_q)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(*double_q))
			*single = !(*single);
		else if (line[i] == '"' && !(*single))
			*double_q = !(*double_q);
		i++;
	}
	return (i);
}

int	check_quotes(const char *line)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	process_quotes(line, &in_single_quote, &in_double_quote);
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

void	handle_exit_too_many_args_error(void)
{
	write(STDERR_FILENO, "exit: too many arguments\n", 25);
}

void	handle_unset_invalid_identifier_error(const char *arg)
{
	write(STDERR_FILENO, "unset: `", 8);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}
