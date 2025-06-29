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


#include "../include/minishell.h"
#include "../include/builtins.h"
#include "../include/exec.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"

int	g_last_status = 0;

static int	execute_builtin_with_redir(t_command *cmd, char ***envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(cmd) != 0)
			exit(1);
		exit(execute_builtin(cmd, envp));
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
	else
	{
		perror("fork");
		return (1);
	}
}

static int	execute_single_command(t_command *cmd, char ***envp)
{
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
		if (cmd->redirs)
			return (execute_builtin_with_redir(cmd, envp));
		else
			return (execute_builtin(cmd, envp));
	}
	else if (cmd->args && cmd->args[0])
		return (execute_external_command(cmd, envp));
	return (0);
}

static void	process_commands(t_command *commands, char ***envp)
{
	t_command	*cmd;

	cmd = commands;
	while (cmd)
	{
		if (cmd->pipe)
		{
			g_last_status = execute_pipeline(cmd, envp);
			while (cmd && cmd->pipe)
				cmd = cmd->next;
			if (cmd)
				cmd = cmd->next;
		}
		else
		{
			g_last_status = execute_single_command(cmd, envp);
			cmd = cmd->next;
		}
	}
}

static void	check_empty_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->value && tmp->value[0] == '\0')
			handle_empty_token_error(tmp->value);
		tmp = tmp->next;
	}
}

static int	process_line(char *line, char ***envp)
{
	t_token		*tokens;
	t_command	*commands;

	if (!check_quotes(line))
		return (1);
	add_history(line);
	tokens = tokenize(line);
	if (!tokens)
		return (1);
	if (!validate_syntax(tokens))
	{
		g_last_status = 2;
		free_tokens(tokens);
		return (1);
	}
	handle_logical_operator(tokens);
	commands = parse_tokens_to_commands(tokens);
	process_commands(commands, envp);
	check_empty_tokens(tokens);
	free_command_list(commands);
	free_tokens(tokens);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	setup_signal_handlers();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (process_line(line, &envp))
		{
			free(line);
			continue ;
		}
		free(line);
	}
	return (0);
}