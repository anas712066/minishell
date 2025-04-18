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
#include <unistd.h>

#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

void	print_command_list(t_command *cmd_list)
{
	int i = 1;
	while (cmd_list)
	{
		printf(CYAN "\n=== Comando %d ===\n" RESET, i++);
		if (cmd_list->args)
		{
			printf(GREEN "Args: " RESET);
			for (int j = 0; cmd_list->args[j]; j++)
				printf("'%s' ", cmd_list->args[j]);
			printf("\n");
		}
		if (cmd_list->infile)
			printf(GREEN "Infile: " RESET "'%s' (heredoc: %d)\n", cmd_list->infile, cmd_list->heredoc);
		if (cmd_list->outfile)
			printf(GREEN "Outfile: " RESET "'%s' (append: %d)\n", cmd_list->outfile, cmd_list->append);
		if (cmd_list->pipe)
			printf(GREEN "Pipe to next command\n" RESET);
		if (cmd_list->logical_or)
			printf(GREEN "Logical OR (||) to next command\n" RESET);
		if (cmd_list->logical_and)
			printf(GREEN "Logical AND (&&) to next command\n" RESET);
		cmd_list = cmd_list->next;
	}
}

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
	t_command *commands;

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
		tokens = tokenize(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		validate_syntax(tokens);
		if (!validate_syntax(tokens))
        {
            free_tokens(tokens);
            free(line);
            continue; // Continuamos con la siguiente línea
        }
		handle_logical_operator(tokens); 
		commands = parse_tokens_to_commands(tokens);
		print_command_list(commands);
		// Procesamos cada comando
		t_command *cmd = commands;
		while (cmd)
		{
			// Si es un builtin
			if (is_builtin(cmd->args[0]))
			{
				execute_builtin(cmd);
			}
			// Si es un comando externo
			else
			{
				return(0);
			}
			cmd = cmd->next;
		}
		tmp = tokens;
		while (tmp)
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
		}
		free_command_list(commands);
		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
