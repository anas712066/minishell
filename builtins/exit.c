/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:48 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 03:52:51 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	is_numeric_with_overflow_check(const char *str, long *result)
{
	char	*endptr;

	if (!str || !*str)
		return (0);
	errno = 0;
	*result = strtol(str, &endptr, 10);
	if (errno == ERANGE)
		return (-1);
	if (*endptr != '\0')
		return (0);
	return (1);
}

static int	handle_exit_args(char **args, int arg_count)
{
	long	exit_code_long;
	int		check_result;

	if (arg_count == 1)
	{
		check_result = is_numeric_with_overflow_check(args[1], &exit_code_long);
		if (check_result == -1)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, args[1], strlen(args[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			exit(2);
		}
		else if (check_result == 0)
		{
			handle_exit_numeric_argument_error(args[1]);
			exit(2);
		}
		exit(exit_code_long & 255);
	}
	return (0);
}

static int	handle_multiple_args(char **args)
{
	long	dummy;
	int		check_result;

	check_result = is_numeric_with_overflow_check(args[1], &dummy);
	if (check_result == -1)
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, args[1], strlen(args[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit(2);
	}
	else if (check_result == 0)
	{
		handle_exit_numeric_argument_error(args[1]);
		exit(2);
	}
	else
	{
		handle_exit_too_many_args_error();
		return (1);
	}
	return (0);
}

int	builtin_exit(char **args)
{
	int	arg_count;

	arg_count = 0;
	while (args[arg_count + 1])
		arg_count++;
	printf("exit\n");
	if (arg_count == 0)
		exit(g_last_status);
	else if (arg_count == 1)
		return (handle_exit_args(args, arg_count));
	else
		return (handle_multiple_args(args));
	return (0);
}
