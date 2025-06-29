/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:06:51 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 16:10:21 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>

char	**add_arg(char **args, char *value)
{
	int		i;
	int		j;
	char	**new_args;

	if (!value || value[0] == '\0')
		return (args);
	i = 0;
	while (args && args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_args[j] = args[j];
		j++;
	}
	new_args[i] = strdup(value);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

static t_command	*process_single_token(t_command *current, t_token **tokens)
{
	if ((*tokens)->type == T_WORD)
		current->args = add_arg(current->args, (*tokens)->value);
	else if ((*tokens)->type == T_REDIR_IN)
		handle_redir_token(current, tokens, T_REDIR_IN);
	else if ((*tokens)->type == T_REDIR_OUT)
		handle_redir_token(current, tokens, T_REDIR_OUT);
	else if ((*tokens)->type == T_APPEND)
		handle_redir_token(current, tokens, T_APPEND);
	else if ((*tokens)->type == T_HEREDOC)
		handle_redir_token(current, tokens, T_HEREDOC);
	else if ((*tokens)->type == T_PIPE)
	{
		current->pipe = 1;
		current->next = new_command();
		current = current->next;
	}
	return (current);
}

t_command	*parse_tokens_to_commands(t_token *tokens)
{
	t_command	*head;
	t_command	*current;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		if (!current)
		{
			current = new_command();
			if (!head)
				head = current;
		}
		current = process_single_token(current, &tokens);
		tokens = tokens->next;
	}
	return (head);
}

static void	free_single_command(t_command *cmd)
{
	t_redir	*redir_tmp;
	int		i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	while (cmd->redirs)
	{
		redir_tmp = cmd->redirs->next;
		free(cmd->redirs->filename);
		free(cmd->redirs);
		cmd->redirs = redir_tmp;
	}
	free(cmd);
}

void	free_command_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_single_command(cmd);
		cmd = tmp;
	}
}
