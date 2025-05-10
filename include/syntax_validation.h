#ifndef SYNTAX_VALIDATION_H
# define SYNTAX_VALIDATION_H

# include "tokenizer.h"

int	handle_logical_operator(t_token *tokens); // Para manejar `||` y `&&`
int	execute_command(t_token *tokens); // Para ejecutar un comando
int	validate_command_exists(const char *command);
int	validate_syntax(t_token *tokens);

#endif