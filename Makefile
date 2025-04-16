# **************************************************************************** #
#                               MINISHELL MAKEFILE                             #
# **************************************************************************** #

# Variables
NAME := minishell
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
INCLUDES := -Iinclude -Ilibft
DEPFLAGS := -MMD -MP

# Directorios
OBJDIR := obj
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

# Colores para mensajes
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

# Archivos fuente
SRCS := src/main.c \
        src/prompt.c \
        src/signal.c \
        src/utils/utils.c \
        parser/tokenizer.c \
        parser/tokenizer_utils.c \
        parser/tokenizer_functions.c \
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

# Objetos y dependencias
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)

# ********************************************** #
#                  RULES                        #
# ********************************************** #

# Regla por defecto
all: $(NAME)

# Incluir la librería libft
$(LIBFT):
	@echo "$(BLUE)Compilando libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# Ejecutable
$(NAME): $(OBJS) $(LIBFT) Makefile
	@echo "$(YELLOW)Enlazando $@...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)¡Minishell compilado correctamente!$(RESET)"

# Regla para compilar .o desde .c
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compilando $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@

# Limpiar archivos objeto
clean:
	@echo "$(PURPLE)Limpiando objetos...$(RESET)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Limpiar todo, incluyendo el ejecutable
fclean: clean
	@echo "$(PURPLE)Limpiando ejecutable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Volver a compilar desde cero
re: fclean all

# Include de dependencias
-include $(DEPS)

.PHONY: all clean fclean re
