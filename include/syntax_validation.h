/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:23:39 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 17:24:12 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_VALIDATION_H
# define SYNTAX_VALIDATION_H

# include "error_handler.h"
# include "tokenizer.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

int		handle_logical_operator(t_token *tokens);
int		execute_command(t_token *tokens);
int		validate_command_exists(const char *command);
int		validate_syntax(t_token *tokens);

void	write_syntax_error(t_token_type type);
int		validate_next_token(t_token *current);
int		validate_redirection(t_token *current);

#endif
