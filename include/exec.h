/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:00 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/28 23:47:22 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include <sys/wait.h>

struct s_command;
typedef struct s_command t_command;

// Prototipos de funciones de ejecución
int	execute_builtin(t_command *cmd, char ***env);
int	execute_external_command(t_command *cmd, char ***envp);
char	*find_binary_in_path(const char *command);
int execute_pipeline(t_command *cmd, char ***envp);
int handle_redirections(t_command *cmd);

#endif
