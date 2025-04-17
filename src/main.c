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
#include <signal.h>

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
	char	*expanded_line;
	t_token	*tokens;
	t_token	*tmp;

	setup_signal_handlers();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (!check_quotes(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		expanded_line = expand_line(line);
		if (!expanded_line)
		{
			fprintf(stderr, "Error: Memory allocation failed\n");
			free(line);
			continue ;
		}
		free(line); // Libera la línea original
		line = expanded_line;

		tokens = tokenize(line);
		if (!tokens)
		{
			fprintf(stderr, "Error: Tokenization failed\n");
			free(line);
			continue ;
		}
		tmp = tokens;
		/*while (tmp)
		{
			if (tmp->value && tmp->value[0] == '\0')
			{
				handle_empty_token_error(tmp->value);
			}
			else
			{
				printf("Token: %-10s Type: %s\n", tmp->value,
					token_type_to_str(tmp->type));
			}
			tmp = tmp->next;
		}*/
		while (tmp)
		{
			// Llama a handle_empty_token_error y verifica si hay un error
			if (tmp->value == NULL || tmp->value[0] == '\0')
			{
				// Si hay un error, pasa al siguiente token
				tmp = tmp->next;
				continue;
			}

			// Procesa el token normalmente si no hay error
			printf("Token: %-10s Type: %s\n", tmp->value, token_type_to_str(tmp->type));
			tmp = tmp->next;
		}
		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	rl_clear_history();
	rl_deprep_terminal();
	clear_history();
	return (0);
}
