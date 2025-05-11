/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:59:28 by mumajeed          #+#    #+#             */
/*   Updated: 2025/05/11 12:59:29 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"

struct s_command;

int builtin_echo(char **args);
int builtin_cd(char **args);
int builtin_pwd(void);
int builtin_export(char **args, char ***env);
int builtin_unset(char **args);
int builtin_env(char **env);
int builtin_exit(char **args);

int is_builtin(const char *cmd);

#endif
