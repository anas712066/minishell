/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:44:54 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/28 17:50:36 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../include/minishell.h"

static int g_signal = 0;

void handle_sigint(int sig)
{
    (void)sig;
    g_signal = SIGINT;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
    g_signal = SIGQUIT;
}

void setup_signal_handlers(void)
{
    if (isatty(STDIN_FILENO))
    {
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);
    }
}
