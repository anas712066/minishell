#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h> // Para malloc, free, getenv
# include <string.h> // Para funciones como strdup
# include "libft.h"  // Para funciones personalizadas como ft_strdup, ft_strjoin

/* Variable global para $? */
extern int g_exit_status;

/* Prototipos de funciones para expansión */
char	*expand_line(const char *line);
char	*expand_variable(const char *line, int *i);

#endif
