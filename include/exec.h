/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:00 by mumajeed          #+#    #+#             */
/*   Updated: 2025/05/02 17:07:55 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

struct s_command;
typedef struct s_command t_command;

// Prototipos de funciones de ejecución
int	execute_builtin(t_command *cmd, char ***env);
int	execute_external_command(t_command *cmd, char ***envp);
char	*find_binary_in_path(const char *command);

#endif
