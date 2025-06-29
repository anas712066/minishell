/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:25 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 17:36:42 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdlib.h>
# include <string.h>
# include "tokenizer.h"

extern int				g_last_status;

typedef struct s_redir
{
	int					type;
	char				*filename;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	int					pipe;
	struct s_command	*next;
}						t_command;

t_command				*parse_tokens_to_commands(t_token *tokens);
void					free_command_list(t_command *cmd);
char					*expand_line(const char *line);
char					*expand_variable(const char *line, int *i);

t_redir					*new_redir(int type, char *filename);

void					add_redir(t_redir **redirs, t_redir *new_redir);
t_command				*new_command(void);
void					handle_word_token(t_command *current, t_token *tokens);
void					handle_redir_token(t_command *current, t_token **tokens,
							int type);
char					**add_arg(char **args, char *value);
char					*expand_variable(const char *line, int *i);
char					*join_and_free(char *result, char *temp);
char					*extract_literal_part(const char *line, int *i);

#endif
