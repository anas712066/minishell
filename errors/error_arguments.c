/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:50:03 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/28 21:24:36 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>

void handle_command_not_found_error(void)
{
    printf("Error: Comando no encontrado.\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:00:00 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/17 12:00:00 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void	handle_cd_too_many_args_error(void)
{
	write(STDERR_FILENO, "cd: too many arguments\n", 23);
}




void	handle_cd_home_not_set_error(void)
{
	write(STDERR_FILENO, "cd: HOME not set\n", 17);
}

void	handle_export_invalid_identifier_error(const char *arg)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, arg, strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}

void	handle_exit_numeric_argument_error(const char *arg)
{
	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, arg, strlen(arg));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
}

void	handle_exit_too_many_args_error(void)
{
	write(STDERR_FILENO, "exit: too many arguments\n", 25);
}

void	handle_unset_invalid_identifier_error(const char *arg)
{
	write(STDERR_FILENO, "unset: `", 8);
	write(STDERR_FILENO, arg, strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}