/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:54:35 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 14:59:49 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	handle_input_redir(t_redir *redir, int *last_infd)
{
	int	fd;

	if (*last_infd != -1)
		close(*last_infd);
	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}
	*last_infd = fd;
	return (0);
}

int	handle_output_redir(t_redir *redir, int *last_outfd)
{
	int	fd;

	if (*last_outfd != -1)
		close(*last_outfd);
	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}
	*last_outfd = fd;
	return (0);
}

int	handle_append_redir(t_redir *redir, int *last_outfd)
{
	int	fd;

	if (*last_outfd != -1)
		close(*last_outfd);
	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}
	*last_outfd = fd;
	return (0);
}

int	check_file_permissions(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, path, strlen(path));
			write(STDERR_FILENO, ": Is a directory\n", 16);
			return (126);
		}
		if (access(path, X_OK) != 0)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, path, strlen(path));
			write(STDERR_FILENO, ": Permission denied\n", 20);
			return (126);
		}
		return (0);
	}
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, path, strlen(path));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	return (127);
}
