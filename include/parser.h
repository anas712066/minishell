/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:25 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/18 17:58:26 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <string.h>
# include "minishell.h"

extern int	g_exit_status;

typedef struct s_redir
{
	int				type; // T_REDIR_IN, T_REDIR_OUT, T_APPEND, T_HEREDOC
	char			*filename; // Archivo asociado a la redirección
	struct s_redir	*next; // Para múltiples redirecciones
}	t_redir;

typedef struct s_command
{
	char	**args; // Argumentos del comando
	char	*infile; // Redirección de entrada (< o <<)
	char	*outfile; // Redirección de salida (> o >>)
	int		append; // 1 si es >>, 0 si es >
	int		heredoc; // 1 si es <<, 0 si es <
	int		pipe; // 1 si hay un pipe después
	int		logical_or; // 1 si hay un || después
	int		logical_and; // 1 si hay un && después
	struct s_command	*next; // Comando siguiente
}	t_command;


t_command	*parse_tokens_to_commands(t_token *tokens);
void		free_command_list(t_command *cmd);
char		*expand_line(const char *line);
char		*expand_variable(const char *line, int *i);

#endif
