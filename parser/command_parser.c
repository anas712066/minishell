// parser/command_parser.c

#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>

static t_command	*new_command(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->pipe = 0;
	cmd->logical_or = 0;
	cmd->logical_and = 0;
	cmd->next = NULL;
	return (cmd);
}

static char	**add_arg(char **args, char *value)
{
	int		i;
	char	**new_args;

	for (i = 0; args && args[i]; i++) ;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	for (int j = 0; j < i; j++)
		new_args[j] = args[j];
	new_args[i] = strdup(value);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

t_command	*parse_tokens_to_commands(t_token *tokens)
{
	t_command	*head = NULL;
	t_command	*current = NULL;

	while (tokens)
	{
		if (!current)
		{
			current = new_command();
			if (!head)
				head = current;
		}
		if (tokens->type == T_WORD)
			current->args = add_arg(current->args, tokens->value);
		else if (tokens->type == T_REDIR_IN)
		{
			tokens = tokens->next;
			current->infile = strdup(tokens->value);
			current->heredoc = 0;
		}
		else if (tokens->type == T_REDIR_OUT)
		{
			tokens = tokens->next;
			current->outfile = strdup(tokens->value);
			current->append = 0;
		}
		else if (tokens->type == T_APPEND)
		{
			tokens = tokens->next;
			current->outfile = strdup(tokens->value);
			current->append = 1;
		}
		else if (tokens->type == T_HEREDOC)
		{
			tokens = tokens->next;
			current->infile = strdup(tokens->value);
			current->heredoc = 1;
		}
		else if (tokens->type == T_PIPE)
		{
			current->pipe = 1;
			current->next = new_command();
			current = current->next;
		}
		else if (tokens->type == T_LOGICAL_OR)
		{
			current->logical_or = 1;
			current->next = new_command();
			current = current->next;
		}
		else if (tokens->type == T_LOGICAL_AND)
		{
			current->logical_and = 1;
			current->next = new_command();
			current = current->next;
		}
		tokens = tokens->next;
	}
	return (head);
}

// parser/command_parser.c

void	free_command_list(t_command *cmd)
{
	t_command *tmp;
	int i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			for (i = 0; cmd->args[i]; i++)
				free(cmd->args[i]);
			free(cmd->args);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
		cmd = tmp;
	}
}
