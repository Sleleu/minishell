# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 15:21:49 by sleleu            #+#    #+#              #
#    Updated: 2022/09/13 19:52:05 by sleleu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./src/libft/libft.a

SRC = src/main.c\
	  src/builtin/echo.c\
	  src/builtin/pwd.c\

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

######### COLORS ##########

END = \033[0m"

GREY = "\x1b[30m
RED = "\033[0;31m
GREEN = "\033[0;32m
YELLOW = "\033[0;33m
BLUE = "\x1b[34m
PURPLE = "\x1b[35m
CYAN = "\x1b[36m
WHITE = "\x1b[37m

all: $(NAME)

$(NAME): $(OBJ)
	make -C src/libft
	$(CC) $(CFLAGS) $(OBJ) -L src/libft -lreadline -lft -g -o $(NAME)
	@echo $(GREEN)			MAKE MINISHELL			$(END)

clean:
	rm -rf $(OBJ)
	make clean -C src/libft
	@echo $(YELLOW)			CLEAN MINISHELL			$(END)

fclean: clean
	rm -rf $(NAME)
	make fclean -C src/libft

re: fclean all
	@echo $(YELLOW)			RE MINISHELL			$(END)

.PHONY: all clean fclean re

.SILENT:
