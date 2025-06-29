/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:00 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 14:59:58 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>

typedef struct s_redir t_redir;
typedef struct s_command t_command;

// Prototipos de funciones de ejecución
int	execute_builtin(t_command *cmd, char ***env);
int	execute_external_command(t_command *cmd, char ***envp);
char	*find_binary_in_path(const char *command);
int execute_pipeline(t_command *cmd, char ***envp);
int handle_redirections(t_command *cmd);

int	handle_append_redir(t_redir *redir, int *last_outfd);
int	handle_output_redir(t_redir *redir, int *last_outfd);
int	handle_input_redir(t_redir *redir, int *last_infd);

int	execute_builtin(t_command *cmd, char ***env);
char	*check_direct_path(const char *command);
char	*search_in_path(const char *command, char *path_copy);

char	*find_binary_in_path(const char *command);
int	handle_empty_command(t_command *cmd);

int	check_file_permissions(const char *path);

#endif
