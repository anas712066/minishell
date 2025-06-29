/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:18 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 14:05:17 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	execute_single_command(t_command *cmd, char ***envp)
{
	if (handle_redirections(cmd) != 0)
		return (1);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
		return (execute_builtin(cmd, envp));
	else
		return (execute_external_command(cmd, envp));
}

static int	execute_first_child(t_command *cmd, int *pipefd, char ***envp)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (handle_redirections(cmd) != 0)
	{
		close(STDOUT_FILENO);
		exit(1);
	}
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, envp));
	else
		exit(execute_external_command(cmd, envp));
}

static int	execute_second_child(t_command *cmd, int *pipefd, char ***envp)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (handle_redirections(cmd->next) != 0)
		exit(1);
	if (cmd->next->pipe)
		exit(execute_pipeline(cmd->next, envp));
	else
	{
		if (cmd->next->args && cmd->next->args[0])
			if (is_builtin(cmd->next->args[0]))
				exit(execute_builtin(cmd->next, envp));
		else
			exit(execute_external_command(cmd->next, envp));
	}
}

static int	wait_for_children(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}

int	execute_pipeline(t_command *cmd, char ***envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!cmd || !cmd->next)
	{
		if (cmd)
			return (execute_single_command(cmd, envp));
		return (0);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid1 = fork();
	if (pid1 == 0)
		execute_first_child(cmd, pipefd, envp);
	pid2 = fork();
	if (pid2 == 0)
		execute_second_child(cmd, pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_for_children(pid1, pid2));
}
