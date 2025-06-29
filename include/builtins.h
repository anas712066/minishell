/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:28 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 03:58:10 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <string.h>

struct	s_command;

int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_pwd(void);
int		builtin_export(char **args, char ***env);
int		builtin_unset(char **args);
int		builtin_env(char **env);
int		builtin_exit(char **args);

int		is_builtin(const char *cmd);
int		is_valid_identifier(const char *name);
int		print_all_exported_vars(char ***env);
int		process_export_arg(char *arg);

#endif
