/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:20 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 13:48:38 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	process_redir(t_redir *current, int *last_infd, int *last_outfd)
{
	if (current->type == T_REDIR_IN)
		return (handle_input_redir(current, last_infd));
	else if (current->type == T_REDIR_OUT)
		return (handle_output_redir(current, last_outfd));
	else if (current->type == T_APPEND)
		return (handle_append_redir(current, last_outfd));
	else if (current->type == T_HEREDOC)
		return (handle_input_redir(current, last_infd));
	return (0);
}

static void	apply_redirections(int last_infd, int last_outfd)
{
	if (last_infd != -1)
	{
		dup2(last_infd, STDIN_FILENO);
		close(last_infd);
	}
	if (last_outfd != -1)
	{
		dup2(last_outfd, STDOUT_FILENO);
		close(last_outfd);
	}
}

int	handle_redirections(t_command *cmd)
{
	t_redir	*current;
	int		last_infd;
	int		last_outfd;

	if (!cmd || !cmd->redirs)
		return (0);
	last_infd = -1;
	last_outfd = -1;
	current = cmd->redirs;
	while (current)
	{
		if (process_redir(current, &last_infd, &last_outfd) != 0)
			return (1);
		current = current->next;
	}
	apply_redirections(last_infd, last_outfd);
	return (0);
}
