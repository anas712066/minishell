/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:44:54 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 20:38:16 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_last_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	g_last_status = 131;
}

void	setup_signal_handlers(void)
{
	if (isatty(STDIN_FILENO))
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
	}
}
