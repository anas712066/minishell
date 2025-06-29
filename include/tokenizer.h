/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:57 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 16:50:33 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "../libft/libft.h"

/* Definición de tipos de token */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
}	t_token_type;

/* Estructura de token */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/* Prototipos de funciones principales */
t_token			*tokenize(char *line);
t_token			*process_token(char *line, int *i);
t_token			*create_token(char *value, t_token_type type);
void			add_token(t_token **tokens, t_token *new);
void			free_tokens(t_token *tokens);

/* Funciones auxiliares del tokenizer - RENOMBRADAS */
t_token			*create_pipe_token(int *i);
t_token			*create_input_redir_token(char *line, int *i);
t_token			*create_output_redir_token(char *line, int *i);
t_token			*create_word_token(char *line, int *i);

/* Funciones de extracción y procesamiento */
char			*extract_word_with_quotes(char *line, int *i);
char			*extract_word(const char *line, int *i);
t_token			*new_token(char *value, t_token_type type);

/* Funciones de utilidad */
void			handle_spaces(char *line, int *i);
int				is_delimiter(char c);
int				is_special_char(char c);
t_token_type	get_type(const char *str, int *len);

/* Funciones de expansión */
char			*expand_variables(char *str);
char			*process_extraction(char *raw_content, int was_in_single_quote);

/* Funciones de srcs/utils/utils.c */
char			*ft_strndup(const char *s, size_t n);
char			*get_history_path(void);

#endif