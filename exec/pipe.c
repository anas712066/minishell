/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:18 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 14:44:04 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "../include/exec.h"
#include "../include/minishell.h"

static int	execute_first_child(t_command *cmd, char ***envp, int *pipefd)
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

static int	execute_second_child(t_command *cmd, char ***envp, int *pipefd)
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
		if (cmd->next->args && cmd->next->args[0] 
			&& is_builtin(cmd->next->args[0]))
			exit(execute_builtin(cmd->next, envp));
		else
			exit(execute_external_command(cmd->next, envp));
	}
}

static int	execute_pipeline_processes(t_command *cmd, char ***envp, 
			int *pipefd)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	pid1 = fork();
	if (pid1 == 0)
		execute_first_child(cmd, envp, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		execute_second_child(cmd, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}

int	execute_pipeline(t_command *cmd, char ***envp)
{
	int		pipefd[2];

	if (!cmd || !cmd->next)
	{
		if (cmd)
		{
			if (handle_redirections(cmd) != 0)
				return (1);
			if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
				return (execute_builtin(cmd, envp));
			else
				return (execute_external_command(cmd, envp));
		}
		return (0);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (execute_pipeline_processes(cmd, envp, pipefd));
}
