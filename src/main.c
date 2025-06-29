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
#include "../include/builtins.h"
#include <signal.h>
#include <unistd.h>
#include "../include/exec.h"
#include <fcntl.h>      // Para open(), O_RDONLY, O_WRONLY, O_CREAT, etc.
#include <string.h> 

extern int g_last_status;  // Variable definida en expand.c

#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

// Función para aplicar redirecciones (para builtins)
int apply_redirections(t_command *cmd)
{
    // Para builtins, usar la misma función que para comandos externos
    return handle_redirections(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_token	*tmp;
	t_command *commands;

	(void)argc;  // Para evitar warning de variable no usada
    (void)argv;
	setup_signal_handlers();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			break ;
		}

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
		if (!validate_syntax(tokens))
        {
			g_last_status = 2;  
            free_tokens(tokens);
            free(line);
            continue; // Continuamos con la siguiente línea
        }
		handle_logical_operator(tokens);
		commands = parse_tokens_to_commands(tokens);
		
		// Procesamos cada comando
		t_command *cmd = commands;
		
		while (cmd)
		{
			if (cmd->pipe)
			{
				// Pipeline
				g_last_status = execute_pipeline(cmd, &envp);
				while (cmd && cmd->pipe)
					cmd = cmd->next;
				if (cmd)
					cmd = cmd->next;
			}
			else
			{
				// Comando simple
				if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
				{
					// Si hay redirecciones, hacer fork (como bash)
					if (cmd->redirs)
					{
						pid_t pid = fork();
						if (pid == 0)
						{
							// Proceso hijo: aplicar redirecciones y ejecutar builtin
							if (handle_redirections(cmd) != 0)
								exit(1);
							exit(execute_builtin(cmd, &envp));
						}
						else if (pid > 0)
						{
							// Proceso padre: esperar al hijo
							int status;
							waitpid(pid, &status, 0);
							if (WIFEXITED(status))
								g_last_status = WEXITSTATUS(status);
							else
								g_last_status = 1;
						}
						else
						{
							perror("fork");
							g_last_status = 1;
						}
					}
					else
					{
						// Sin redirecciones: ejecutar builtin directamente
						g_last_status = execute_builtin(cmd, &envp);
					}
				}
				else if (cmd->args && cmd->args[0])
				{
					// Para comandos externos, la redirección ya está en execute_external_command
					g_last_status = execute_external_command(cmd, &envp);
				}
				cmd = cmd->next;
			}
		}
		tmp = tokens;
		while (tmp)
		{
			if (tmp->value && tmp->value[0] == '\0')
			{
				handle_empty_token_error(tmp->value);
			}
			tmp = tmp->next;
		}
		free_command_list(commands);
		free_tokens(tokens);
		free(line);
	}
	return (0);
}