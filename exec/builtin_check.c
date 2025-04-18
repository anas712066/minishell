/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:04:10 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/18 18:14:53 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/minishell.h"
#include "../include/parser.h"

int is_builtin(const char *cmd)
{
	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") || !strcmp(cmd, "pwd") ||
			!strcmp(cmd, "export") || !strcmp(cmd, "unset") ||
			!strcmp(cmd, "env") || !strcmp(cmd, "exit"));
}


