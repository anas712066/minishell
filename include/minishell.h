/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:10:27 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/28 19:07:27 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokenizer.h"
# include "error_handler.h"
# include "../libft/libft.h"
# include "signal1.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"
# include "syntax_validation.h"
# include "env.h"

extern int g_last_exit_code;

#endif
