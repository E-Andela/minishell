# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: eandela <eandela@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2024/12/12 14:24:59 by eandela       #+#    #+#                  #
#    Updated: 2024/12/12 22:07:21 by eandela       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
LINKER = -lreadline

SOURCE_DIR = ./src
OBJECT_DIR = ./obj

SOURCES = 	builtin_utils.c \
			debugging.c \
			env_parsing.c \
			error_handling.c \
			exec.c \
			expander.c \
			free_and_exit.c \
			ft_echo.c \
			ft_env.c \
			ft_envp.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			here_doc.c \
			parser.c \
			tokenizer.c \
			tokens_utils.c \
			new_exec.c \
			main.c

LIBFTNAME = libft.a
LIBFTDIR = ./libft

OBJECTS = $(SOURCES:%.c=$(OBJECT_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFTDIR)
	@cc $(CFLAGS) $(LINKER) $(OBJECTS) $(LIBFTDIR)/$(LIBFTNAME) -o $(NAME)
	
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(OBJECT_DIR)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECT_DIR)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean
	
re: fclean all