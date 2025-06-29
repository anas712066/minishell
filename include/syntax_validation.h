#ifndef SYNTAX_VALIDATION_H
# define SYNTAX_VALIDATION_H

# include "tokenizer.h"

# include "error_handler.h"
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>

int	handle_logical_operator(t_token *tokens); // Para manejar `||` y `&&`
int	execute_command(t_token *tokens); // Para ejecutar un comando
int	validate_command_exists(const char *command);
int	validate_syntax(t_token *tokens);

void	write_syntax_error(t_token_type type);
int	validate_next_token(t_token *current);
int	validate_redirection(t_token *current);

#endif