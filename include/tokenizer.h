/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:57 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/16 19:28:48 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>
# include "libft.h"

/* Definición de tipos de token */
typedef enum e_token_type
{
	T_WORD, /* Palabra/identificador general */
	T_PIPE, /* | */
	T_REDIR_IN, /* < */
	T_REDIR_OUT, /* > */
	T_APPEND, /* >> */
	T_HEREDOC, /* << */
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
