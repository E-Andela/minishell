# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: eandela <marvin@42.fr>                       +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/19 12:27:38 by eandela       #+#    #+#                  #
#    Updated: 2025/01/23 13:39:51 by livliege      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

CC			= cc
CFLAGS 		= -Wall -Wextra -Werror
OBJDIR 		= .obj_lib

SRC =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_printf_charstring.c \
		ft_printf_hexadecimalsptr.c \
		ft_printf_number.c \
		ft_printf_unsigned_number.c \
		ft_printf.c	\
		get_next_line_bonus.c \
		get_next_line_utils.c

OBJECTS 	= $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
