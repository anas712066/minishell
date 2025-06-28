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

int g_last_exit_code = 0;

#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

// Función para validar redirecciones antes de ejecutar
int validate_redirections(t_command *cmd)
{
    // Validar archivo de entrada
    if (cmd->infile)
    {
        if (access(cmd->infile, F_OK) == -1)
        {
            write(STDERR_FILENO, "minishell: ", 11);
            write(STDERR_FILENO, cmd->infile, strlen(cmd->infile));
            write(STDERR_FILENO, ": No such file or directory\n", 28);
            return (1);  // Error
        }
        if (access(cmd->infile, R_OK) == -1)
        {
            write(STDERR_FILENO, "minishell: ", 11);
            write(STDERR_FILENO, cmd->infile, strlen(cmd->infile));
            write(STDERR_FILENO, ": Permission denied\n", 20);
            return (1);  // Error
        }
    }
    
    // Validar archivo de salida (solo el directorio padre)
    if (cmd->outfile)
    {
        // Aquí podrías validar si el directorio padre existe y es escribible
        // Por ahora, lo dejamos para que open() maneje el error
    }
    
    return (0);  // Todo correcto
}

// Función para aplicar redirecciones (separada de la validación)
int apply_redirections(t_command *cmd)
{
    // Redirección de entrada (<)
    if (cmd->infile)
    {
        int fd = open(cmd->infile, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            return (1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    
    // Redirección de salida (> o >>)
    if (cmd->outfile)
    {
        int flags = O_WRONLY | O_CREAT;
        if (cmd->append)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;
            
        int fd = open(cmd->outfile, flags, 0644);
        if (fd == -1)
        {
            perror("open");
            return (1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    
    return (0);  // Éxito
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	//char	*value;
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
			printf("\n");
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
            free_tokens(tokens);
            free(line);
            continue; // Continuamos con la siguiente línea
        }
		handle_logical_operator(tokens);  //esta esta mal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		commands = parse_tokens_to_commands(tokens);
		//print_command_list(commands);
		// Procesamos cada comando
		t_command *cmd = commands;
		while (cmd)
		{
			// PRIMERO: Validar redirecciones
			if (validate_redirections(cmd) != 0)
			{
				g_last_exit_code = 1;  // Error en redirecciones
				cmd = cmd->next;
				continue;
			}
			
			if (cmd->pipe)
			{
				// Pipeline
				g_last_exit_code = execute_pipeline(cmd, &envp);
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
					// Para builtins, aplicar redirecciones aquí
					int stdin_backup = dup(STDIN_FILENO);
					int stdout_backup = dup(STDOUT_FILENO);
					
					if (apply_redirections(cmd) == 0)
					{
						g_last_exit_code = execute_builtin(cmd, &envp);
					}
					else
					{
						g_last_exit_code = 1;
					}
					
					// Restaurar file descriptors
					dup2(stdin_backup, STDIN_FILENO);
					dup2(stdout_backup, STDOUT_FILENO);
					close(stdin_backup);
					close(stdout_backup);
				}
				else if (cmd->args && cmd->args[0])
				{
					// Para comandos externos, la redirección ya está en execute_external_command
					g_last_exit_code = execute_external_command(cmd, &envp);
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
			/*
			else
			{
				printf("Token: %-10s Type: %s\n", tmp->value,
					token_type_to_str(tmp->type));
			}
			*/
			
			tmp = tmp->next;
		}
		free_command_list(commands);
		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
