
vpath %.c src src/builtins src/errors_and_exit src/executor src/expander src/parser src/tokenizer src/signals
vpath %.h inc

NAME = minishell

CFLAGS = #-Wall -Wextra -Werror
LINKER = -lreadline

SOURCE_DIR = ./src
OBJECT_DIR = ./obj

LIBFTDIR = ./libft
LIBFTNAME = libft.a
LIBFT = $(LIBFTDIR)/$(LIBFTNAME)

SOURCES = 	\
			builtin_utils.c \
			export_utils.c \
			export_utils2.c \
			ft_cd.c \
			ft_echo.c \
			ft_env.c \
			ft_exit.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			\
			error_handling.c \
			free_and_exit.c \
			\
			exec.c \
			new_exec.c \
			ft_envp.c \
			here_doc.c \
			\
			expander_utils.c \
			expander.c \
			vectors.c \
			\
			env_parsing.c \
			parser_init_nodes.c \
			parser.c \
			\
			tokenizer.c \
			tokenizer_utils.c \
			tokens_create.c \
			\
			signal_handlers.c \
			signal_init.c \
			\
			debugging.c \
			main.c \

OBJECTS = $(patsubst %.c, $(OBJECT_DIR)/%.o, $(SOURCES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@echo "Building $(NAME)..."
	@cc $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBFT) $(LINKER) -g
# -fsanitize=address

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
