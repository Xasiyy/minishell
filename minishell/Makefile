# =================================== CONFIG =================================== #

NAME        = minishell
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -Iinclude -Ilibft -Iget_next_line -O0 -g
BIN_DIR     = bin
OBJ_DIR     = obj
SRC_DIR     = src

# --- Libft -------------------------------------------------------------------- #
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# --- ft_printf ---------------------------------------------------------------- #
FT_PRINTF_DIR   = ft_printf
FT_PRINTF_SRCS  = ft_printf.c ft_put.c handle_char.c ft_functions.c
FT_PRINTF_OBJS  = $(addprefix $(OBJ_DIR)/$(FT_PRINTF_DIR)/,$(FT_PRINTF_SRCS:.c=.o))

GNL_DIR		= get_next_line
GNL_SRCS	= $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS	= $(addprefix $(OBJ_DIR)/,$(GNL_SRCS:.c=.o))

# --- Projet minishell --------------------------------------------------------- #
SRCS = builtins/builtins_cd.c \
       builtins/builtins_core.c \
       builtins/builtins_echo.c \
       builtins/builtins_env.c \
       builtins/builtins_exit.c \
       builtins/builtins_exit_parent_child.c \
       builtins/builtins_export.c \
       builtins/builtins_utils.c \
       builtins/heredoc.c \
       command_path/command_path.c \
       context_env/context_env.c \
       env/env_display.c \
       env/env_unset.c \
       env/env_utils.c \
       execution/child_utils.c \
       execution/execution_child.c \
       execution/execution.c \
       execution/execve_handler.c \
       execution/handle_redirections.c \
       execution/pipeline.c \
       execution/redirections.c \
       free/free_shell.c \
       free/free_utils.c \
       free/memory_utils.c \
       free/clean_exit.c \
       free/safe_close.c \
       helpers/env_helpers.c \
       helpers/execution_helpers.c \
       line_handler/line_handler.c \
       main/main.c \
       parsing/expander.c \
       parsing/parsing_check.c \
       parsing/parsing_entry.c \
       parsing/parsing.c \
       parsing/parsing_trim.c \
       parsing/parsing_utils.c \
       parsing/parsing_tok.c \
       parsing/parsing_tokens.c \
       parsing/parsing_redirec.c \
       parsing/parsing_redirection.c \
       parsing/parsing_syntax.c \
       parsing/parsing_pipeline.c \
       parsing/split_pipeline.c \
       parsing/segmentation_quotes.c \
       parsing/split_internat_redirs.c \
       parsing/split_quotes.c \
       parsing/parsing_field_splitting.c \
       shell_main/shell_main.c \
       signal/signals.c \
       utils/file_utils.c \
       utils/ft_strdup_array.c

OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions=valgrind.supp

# ================================ COMPILATION ================================= #

all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(LIBFT) $(OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)
	@mkdir -p $(BIN_DIR)
	@printf "$(GREEN)[Linking]$(RESET) Creating executable: $(NAME)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS) -lreadline $(LIBFT) -o $@
	@printf "$(GREEN)[Success]$(RESET) Build complete 🎉\n"

# ---------- Libft ------------------------------------------------------------- #
$(LIBFT):
	@printf "$(BLUE)[Libft]$(RESET) Compiling libft...\n"
	@$(MAKE) -sC $(LIBFT_DIR)

# ---------- Sources minishell ------------------------------------------------- #
# Couleurs
GREEN := \033[0;32m
BLUE := \033[0;34m
RESET := \033[0m

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# ---------- Sources ft_printf ------------------------------------------------- #

$(OBJ_DIR)/$(FT_PRINTF_DIR)/%.o: $(FT_PRINTF_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# ================================ UTILITAIRES ================================= #

vg: $(BIN_DIR)/$(NAME)
	$(VALGRIND) ./$(BIN_DIR)/$(NAME)
       $(BIN_DIR)/$(NAME): $(LIBFT) $(OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)
	@mkdir -p $(BIN_DIR)
	@printf "$(GREEN)[Linking]$(RESET) Creating executable: $(NAME)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS) -lreadline $(LIBFT) -o $@

	@printf "$(BLUE)[Progress]$(RESET) "
	@i=0; while [ $$i -le 20 ]; do \
		printf "#"; \
		sleep 0.05; \
		i=`expr $$i + 1`; \
	done; \
	printf " 100%%\n"
	@printf "$(GREEN)[Success]$(RESET) Build complete 🎉\n"


clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(BIN_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re vg
