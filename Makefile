# **************************************************************************** #
#                               MINIHELL MAKEFILE                              #
# **************************************************************************** #

NAME        := minishell

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -g
INCLUDES    := -Iinclude -Ilibft

# Directorios de los archivos fuente
SRC_DIRS    := src parser builtins exec
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

# Archivos fuente y objetos manuales
SRCS        := src/main.c \
               src/prompt.c \
               src/signal.c \
               src/utils/ft_xxx.c \
               parser/tokenizer.c \
               parser/quotes.c \
               parser/expand.c \
               parser/parser_utils.c \
               builtins/echo.c \
               builtins/cd.c \
               builtins/pwd.c \
               builtins/env.c \
               builtins/export.c \
               builtins/unset.c \
               builtins/exit.c \
               exec/exec.c \
               exec/redir.c \
               exec/pipe.c \
               exec/builtin_check.c

OBJS        := $(SRCS:.c=.o)

# ********************************************** #
#                  RULES                        #
# ********************************************** #

# Regla por defecto
all: $(LIBFT) $(NAME)

# Incluir la librería libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Regla para compilar el ejecutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Limpiar archivos objeto
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Limpiar todo, incluyendo el ejecutable
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Volver a compilar desde cero
re: fclean all

# Regla para compilar .o desde .c
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Incluir los archivos de dependencias generados automáticamente
-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
