
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
