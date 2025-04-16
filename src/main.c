/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:06:33 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/16 16:06:35 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/minishell.h"

const char	*token_type_to_str(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_APPEND)
		return ("APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

int	main(void)
{
	char	*line;
	t_token	*tokens;
	t_token	*tmp;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;

		// Verificar si las comillas están emparejadas antes de continuar
		if (!check_quotes(line))
		{
			handle_quote_error(1);
			continue ;
		}

		// Si las comillas están bien, agregar al historial
		add_history(line);

		// Tokenizar la línea
		tokens = tokenize(line);
		tmp = tokens;

		// Verificar y manejar tokens vacíos
		while (tmp)
		{
			if (tmp->value && tmp->value[0] == '\0')  // Token vacío
			{
				handle_empty_token_error(tmp->value);
			}
			else
			{
				printf("Token: %-10s Type: %s\n", tmp->value,
					token_type_to_str(tmp->type));
			}
			tmp = tmp->next;
		}

		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
