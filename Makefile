# **************************************************************************** #
#                               MINISHELL MAKEFILE                             #
# **************************************************************************** #

# Variables
NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror #-fsanitize=address -fsanitize=undefined
INCLUDES := -Iinclude -Ilibft
DEPFLAGS := -MMD -MP

# Directories
OBJDIR := obj
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

# Colores pfor messages
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

# Objects files
SRCS := src/main.c \
        src/main_utils.c \
        src/signal.c \
        src/utils/utils.c \
        src/utils/history_utils.c \
        src/syntax_validation.c \
        src/syntax_validation_utils.c \
        parser/tokenizer.c \
        parser/tokenizer_utils.c \
        parser/tokenizer_utils2.c \
        parser/tokenizer_functions.c \
        parser/expand.c \
        parser/expand_utils.c \
        parser/command_parser.c \
        parser/command_parser_utils.c \
        parser/variable_expansion.c \
        builtins/echo.c \
        builtins/cd.c \
        builtins/pwd.c \
        builtins/env.c \
        builtins/export.c \
        builtins/export_utils.c \
        builtins/unset.c \
        builtins/exit.c \
        exec/exec.c \
        exec/exec_utils.c \
        exec/redir.c \
        exec/redir_utils.c \
        exec/pipe.c \
        exec/builtin_check.c \
        errors/error_handler.c \
        errors/error_quotes.c \
        errors/error_arguments.c \
        errors/error_tokens.c \

# Objets and dependencies
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)

# **********************************************
#                  RULES                        
# **********************************************

# Rule by default
all: $(NAME)

# Include libft
$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# Executable
$(NAME): $(OBJS) $(LIBFT) Makefile
	@echo "$(YELLOW)Linking $@...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "$(GREEN)¡Minishell compiled successfully!$(RESET)"

# Rule for compiling .o from .c
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "$(PURPLE)Cleaning objects...$(RESET)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Clean everything, including the executable
fclean: clean
	@echo "$(PURPLE)Cleaning Executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Recompile from scratch
re: fclean all

# Include dependencies
-include $(DEPS)

.PHONY: all clean fclean re
