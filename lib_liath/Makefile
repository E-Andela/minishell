NAME 				= lib_liath.a
CC					= cc
CFLAGS 				= -Wall -Werror -Wextra
OBJDIR				= .obj_lib
SRC_DIR				= src
SRC 				= 	ft_bzero.c \
						ft_calloc.c \
						ft_isalnum.c \
						ft_memset.c \
						ft_putchar_fd.c \
						ft_putendl_fd.c \
						ft_putstr_fd.c \
						ft_split.c \
						ft_strchr.c \
						ft_strdup.c \
						ft_strlcat.c \
						ft_strlen.c \
						ft_strncmp.c \
						ft_strtrim.c \
						ft_substr.c	
OBJ					= $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $^

clean:
	@-rm -rf $(OBJDIR)

fclean: clean
	@echo "Removing the lib_liath.a file."
	@-rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re