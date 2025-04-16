#include "../include/minishell.h"
#include "../include/tokenizer.h"
#include <stdio.h>

void	validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (!current->value || current->value[0] == '\0')
			handle_empty_token_error(current->value);
		current = current->next;
	}
}

void	handle_empty_token_error(const char *token)
{
	if (token == NULL || token[0] == '\0')
	{
		printf("Error: Token vacío detectado.\n");
	}
}
