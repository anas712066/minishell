/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:24:25 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 14:54:40 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/minishell.h"
#include <stdlib.h>
#include <string.h>

static t_redir	*new_redir(int type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	redir->next = NULL;
	return (redir);
}

static void	add_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*current;

	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	current = *redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

static t_command	*new_command(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	return (cmd);
}

static char	**add_arg(char **args, char *value)
{
	int	i;
	int	j;
	char	**new_args;

	i = 0;
	while (args && args[i])
		i++;
	return (NULL);
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	j = -1;
	while (++j < i)
		new_args[j] = args[j];
	new_args[i] = ft_strdup(value);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
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
		if (tokens->type == T_WORD)
			current->args = add_arg(current->args, tokens->value);
		else if (tokens->type == T_REDIR_IN)
		{
			tokens = tokens->next;
			add_redir(&current->redirs, new_redir(T_REDIR_IN, tokens->value));
		}
		else if (tokens->type == T_REDIR_OUT)
		{
			tokens = tokens->next;
			add_redir(&current->redirs, new_redir(T_REDIR_OUT, tokens->value));
		}
		else if (tokens->type == T_APPEND)
		{
			tokens = tokens->next;
			add_redir(&current->redirs, new_redir(T_APPEND, tokens->value));
		}
		else if (tokens->type == T_HEREDOC)
		{
			tokens = tokens->next;
			add_redir(&current->redirs, new_redir(T_HEREDOC, tokens->value));
		}
		else if (tokens->type == T_PIPE)
		{
			current->pipe = 1;
			current->next = new_command();
			current = current->next;
		}
		tokens = tokens->next;
	}
	return (head);
}

void free_command_list(t_command *cmd)
{
	t_command	*tmp;
	t_redir		*redir_tmp;
	int	i;

    while (cmd)
    {
        tmp = cmd->next;

        if (cmd->args)
        {
            for (i = 0; cmd->args[i]; i++)
                free(cmd->args[i]);
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
        cmd = tmp;
    }
}
