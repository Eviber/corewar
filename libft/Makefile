# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 02:18:15 by ygaude            #+#    #+#              #
#    Updated: 2018/04/06 11:17:15 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

SRC = ft_abs.c ft_atoi.c ft_atol.c ft_bzero.c ft_imaxtoa.c                     \
	  ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c         \
	  ft_isspace.c ft_itoa.c ft_lstadd.c ft_lstaddend.c ft_lstdel.c            \
	  ft_lstdelone.c ft_lstend.c ft_lstiter.c ft_lstmap.c ft_lstnew.c          \
	  ft_magnitude.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c        \
	  ft_memcpy.c ft_memdel.c ft_memdup.c ft_memjoin.c ft_memmove.c ft_memset.c\
	  ft_pr_apply.c ft_pr_convert.c ft_pr_loop.c ft_pr_parse.c ft_printf.c     \
	  ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c    \
	  ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strappend.c ft_strcat.c     \
	  ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c  \
	  ft_strequ.c ft_strinsert.c ft_striter.c ft_striteri.c ft_strjoin.c       \
	  ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strmerge.c          \
	  ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c          \
	  ft_strnlen.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c         \
	  ft_strsub.c ft_strtoupper.c ft_strtrim.c ft_tolower.c                    \
	  ft_toupper.c ft_uimaxtoa.c get_next_line.c ft_memalloc_exit.c

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "Compiling... $(CC) $(CFLAGS) -c -o %-39s\r" "$@ $^"
	@$(CC) $(CFLAGS) -c -o $@ $^

$(NAME): $(OBJ)
	@printf "%101c\rCompiling....\033[32m✔\033[0m\n" ' '
	@printf "Linking......"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\033[32m✔\033[0m\n"
	@echo "Done !"

clean:
	@printf "Object files...\r"
	@rm -rf $(OBJ_DIR)
	@printf "Object files removed.\n"

fclean: clean
	@printf "$(NAME)...\r"
	@rm -f $(NAME)
	@printf "$(NAME) removed.\n"

re: fclean all

.PHONY: all clean fclean re
