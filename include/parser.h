/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:25 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 14:29:46 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <string.h>
# include "minishell.h"

extern int	g_last_status;

typedef struct s_redir
{
	int				type; // T_REDIR_IN, T_REDIR_OUT, T_APPEND, T_HEREDOC
	char			*filename; // Archivo asociado a la redirección
	struct s_redir	*next; // Para múltiples redirecciones
}	t_redir;

typedef struct s_command
{
	char	**args; // Argumentos del comando
	t_redir         *redirs;    // Lista de redirecciones
    int             pipe;       // 1 si hay pipe después de este comando
	struct s_command	*next; // Comando siguiente
}	t_command;


t_command	*parse_tokens_to_commands(t_token *tokens);
void		free_command_list(t_command *cmd);
char		*expand_line(const char *line);
char		*expand_variable(const char *line, int *i);

#endif
