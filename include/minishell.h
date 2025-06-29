/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:10:27 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 17:19:11 by mmilitar         ###   ########.fr       */
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

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#endif
