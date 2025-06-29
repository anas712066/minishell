/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:41:53 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 17:41:55 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_UTILS_H
# define MAIN_UTILS_H

# include "../include/minishell.h"
# include "../include/tokenizer.h"
# include "../include/parser.h"

/* Funciones de ejecución de comandos */
int		execute_builtin_with_redir(t_command *cmd, char ***envp);
int		execute_single_command(t_command *cmd, char ***envp);

/* Funciones de procesamiento */
void	process_commands(t_command *commands, char ***envp);
int		process_line(char *line, char ***envp);

/* Funciones de utilidad */
void	check_empty_tokens(t_token *tokens);

#endif
