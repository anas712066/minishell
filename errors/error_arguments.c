/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:50:03 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/17 00:36:01 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>

void	handle_redir_error(void)
{
	printf("Error: Redirección mal formada.\n");
}

void	handle_command_not_found_error(void)
{
	printf("Error: Comando no encontrado.\n");
}

void	handle_missing_argument_error(const char *command)
{
	printf("Error: El comando '%s' requiere al menos un argumento.\n", command);
}

void	handle_invalid_redir_error(void)
{
	printf("Error: Redirección mal formada (falta archivo).\n");
}

void	handle_invalid_pipe_error(void)
{
	printf("Error: Pipe mal colocado.\n");
}
