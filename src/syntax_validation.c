/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:02:31 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 17:17:18 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_validation.h"

static int	validate_pipe(t_token *current, t_token *tokens)
{
	if (current == tokens || !current->next)
	{
		write(STDERR_FILENO, " syntax error near unexpected token `|'\n", 40);
		return (0);
	}
	else if (current->next->type == T_PIPE)
	{
		write(STDERR_FILENO, " syntax error near unexpected token `|'\n", 40);
		return (0);
	}
	return (1);
}

static int	validate_quotes(t_token *current)
{
	if (current->value && (current->value[0] == '"'
			|| current->value[0] == '\''))
	{
		if (!check_quotes(current->value))
			return (0);
	}
	return (1);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == T_REDIR_OUT || current->type == T_APPEND
			|| current->type == T_REDIR_IN || current->type == T_HEREDOC)
		{
			if (!validate_redirection(current))
				return (0);
		}
		if (current->type == T_PIPE)
		{
			if (!validate_pipe(current, tokens))
				return (0);
		}
		if (!validate_quotes(current))
			return (0);
		current = current->next;
	}
	return (1);
}

static int	execute_child_process(char *full_path, char **argv)
{
	if (execve(full_path, argv, NULL) == -1)
	{
		perror("execve failed");
		exit(1);
	}
	return (0);
}

int	execute_command(t_token *tokens)
{
	pid_t	pid;
	int		status;
	char	*argv[2];
	char	*path;
	char	full_path[256];

	argv[0] = tokens->value;
	argv[1] = NULL;
	path = "/bin/";
	snprintf(full_path, sizeof(full_path), "%s%s", path, tokens->value);
	pid = fork();
	if (pid == 0)
		return (execute_child_process(full_path, argv));
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork failed");
		return (1);
	}
	return (0);
}
