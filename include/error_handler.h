/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:11:40 by mmilitar          #+#    #+#             */
/*   Updated: 2025/05/11 12:59:50 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include "tokenizer.h"

void	handle_quote_error(int type);
void	handle_empty_token_error(const char *token);
void	handle_redir_error(void);
void	handle_missing_argument_error(const char *cmd);
void	handle_invalid_redir_error(void);
void	handle_command_not_found_error(void);
int		check_quotes(const char *line);
void	validate_tokens(t_token *tokens);
void	handle_invalid_pipe_error(void);

#endif
