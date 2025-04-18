/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:57 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/17 10:52:12 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>
# include "../libft/libft.h"

/* Definición de tipos de token */
typedef enum e_token_type
{
	T_WORD, /* Palabra/identificador general */
	T_PIPE, /* | */
	T_REDIR_IN, /* < */
	T_REDIR_OUT, /* > */
	T_APPEND, /* >> */
	T_HEREDOC, /* << */
	T_LOGICAL_OR, // Para ||
	T_LOGICAL_AND, // Para &&
	T_UNKNOWN,
}	t_token_type;

/* Estructura de token */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/* Prototipos de funciones para token_utils.c */

t_token			*process_token(char *line, int *i);
int				is_special_char(char c);

/*Funcion de srcs/utils/utils.c*/
char			*ft_strndup(const char *s, size_t n);
char			*get_history_path(void);

/* Prototipos de funciones para tokenizer.c */
t_token_type	get_type(const char *str, int *len);
t_token			*tokenize(char *line);
char			*extract_word(const char *line, int *i);
t_token			*new_token(char *value, t_token_type type);
void			add_token(t_token **tokens, t_token *new);

/* Prototipos de funciones para liberar memoria */
void			free_tokens(t_token *tokens);
void			handle_spaces(char *line, int *i);

#endif
