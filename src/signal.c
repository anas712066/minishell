/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:44:54 by mmilitar          #+#    #+#             */
/*   Updated: 2025/05/14 14:01:15 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include "../include/minishell.h"

extern int g_exit_status;

void	handle_sigint(int sig)
{
    (void)sig;
    g_exit_status = 130; // Código de salida para Ctrl+C
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();       // Indica que estamos en una nueva línea
    rl_replace_line("", 0); // Limpia la línea actual
    rl_redisplay();         // Redibuja el prompt
}

void	handle_sigquit(int sig)
{
    (void)sig;
    g_exit_status = 131; /*// Código de salida para Ctrl+\
    // No hacemos nada más (comportamiento como bash)*/
}

void	setup_signal_handlers(void)
{
    // Configura los manejadores de señales solo en modo interactivo
    if (isatty(STDIN_FILENO))
    {
        signal(SIGINT, handle_sigint);   // Ctrl+C
        signal(SIGQUIT, handle_sigquit); /*// Ctrl+\*/
    }
}
