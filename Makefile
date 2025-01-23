
vpath %.c src src/builtins src/environment_list src/errors_and_exit src/executor src/expander src/parser src/tokenizer src/signals
vpath %.h inc

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
LINKER = -lreadline

SOURCE_DIR = ./src
OBJECT_DIR = ./obj

LIBFTDIR = ./libft
LIBFTNAME = libft.a
LIBFT = $(LIBFTDIR)/$(LIBFTNAME)

SOURCES = 	\
			builtins/builtin_utils.c \
			builtins/export_utils.c \
			builtins/export_utils2.c \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c \
			builtins/ft_exit.c \
			builtins/ft_export.c \
			builtins/ft_pwd.c \
			builtins/ft_unset.c \
			\
			environment_list/env_helpers.c \
			environment_list/env_list_utils.c \
			environment_list/env_list.c \
			\
			errors_and_exit/error_handling.c \
			errors_and_exit/free_and_exit.c \
			errors_and_exit/free_lists.c \
			\
			executor/command_path.c \
			executor/execution_utils.c \
			executor/execution.c \
			executor/here_doc.c \
			executor/pipes.c \
			executor/redirections.c \
			\
			expander/expander_utils.c \
			expander/expander.c \
			expander/handle_environment.c \
			expander/handle_quotes.c \
			expander/vectors.c \
			\
			parser/parser_init_nodes.c \
			parser/parser_utils.c \
			parser/parser.c \
			\
			signals/signal_handlers.c \
			signals/signal_init.c \
			\
			tokenizer/tokenizer.c \
			tokenizer/tokenizer_utils.c \
			tokenizer/tokens_create.c \
			\
			utils/shell_lvl.c \
			utils/tester.c \
			\
			debugging.c \
			main.c


OBJECTS = $(patsubst %.c, $(OBJECT_DIR)/%.o, $(SOURCES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@echo "Building $(NAME)..."
	@cc $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBFT) $(LINKER) -g 
#-fsanitize=address

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFTDIR)

$(OBJECT_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< into $@..."
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECT_DIR)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean
	
re: fclean all
