# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 15:21:49 by sleleu            #+#    #+#              #
#    Updated: 2022/09/14 16:56:27 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
CC				= 	gcc
FLAGS			= 	-Wall -Wextra -Werror

### EXECUTABLE ###
NAME			= 	minishell
PROG			= 	minishell

### PATHS ###
INCLUDE			= 	include
LIBFT_PATH		= 	libft
SRC_PATH		= 	src
OBJ_PATH		= 	obj

### SOURCE FILES ###
SOURCES 		= 	main.c \
					builtin/echo.c \
					builtin/pwd.c \
					builtin/env.c \
					builtin/unset.c \
					parsing/parser.c \
					parsing/pipe.c \
					parsing/free.c \

### OBJECTS ###
SRC				= 	$(addprefix $(SRC_PATH)/,$(SOURCES))
OBJ				= 	$(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

### COLORS ###
NOC				= 	\033[0m
RED				= 	\033[1;31m
GREEN			= 	\033[1;32m
YELLOW			= 	\033[1;33m
BLUE			= 	\033[1;34m
WHITE			= 	\033[1;37m

### RULES ###

# ------- ALL

all: 	$(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)libft..$(NOC)"
	@make -sC $(LIBFT_PATH)
	@$(CC) $(FLAGS) -L $(LIBFT_PATH) -o $(PROG) $^ -lft
	@echo "$(GREEN)$@ ✅$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDE)/$(NAME).h
	@mkdir -p obj && mkdir -p obj/builtin && mkdir -p obj/parsing
	@$(CC) $(FLAGS) -I$(INCLUDE) -c -o $@ $<
	@echo "$(BLUE)gcc $(WHITE)$(notdir $@)$(NOC)"

# ------- Clean

clean:
	@echo "$(RED)clean$(NOC)"
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

# ------- Gadget

norm:
	-@norminette $(SRC_PATH)
	-@norminette $(SRC_BONUS_PATH)
	-@norminette $(INCLUDE)

push: fclean
	git add .
	git status
	git commit -m minishell
	git push

.PHONY:	 default mandatory clean fclean re norm push