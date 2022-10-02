# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 15:21:49 by sleleu            #+#    #+#              #
#    Updated: 2022/10/02 19:20:58 by sleleu           ###   ########.fr        #
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
					init/utils.c \
					builtin/cd.c \
					builtin/echo.c \
					builtin/exit.c \
					builtin/pwd.c \
					builtin/env.c \
					builtin/unset.c \
					builtin/export.c \
					builtin/export_is_var.c \
					builtin/export_utils.c \
					parsing/parser.c \
					parsing/init_parsing.c \
					parsing/parser_utils.c \
					parsing/token_type_error.c \
					parsing/convert_env.c \
					parsing/convert_env_utils.c \
					parsing/parse_quotes.c \
					memcenter/memcenter.c \
					lexer/lexer.c \
					lexer/is_token.c \
					lexer/lexer_utils.c \
					lexer/handle_quotes.c \
					exec/exec.c \
					exec/execution.c \
					exec/utils.c \
					exec/utils_one.c \
					exec/utils_two.c \
					exec/fd_manager.c \
					signal/signal.c \

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
	@$(CC) $(FLAGS) -L $(LIBFT_PATH) -o $(PROG) $^ -lft -lreadline
	@echo "$(GREEN)Welcome to $@ ✅$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDE)/$(NAME).h
	@mkdir -p obj && mkdir -p obj/builtin && mkdir -p obj/parsing && mkdir -p obj/lexer && mkdir -p obj/memcenter && mkdir -p obj/init && mkdir -p obj/exec -p obj/signal
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

re: fclean
	make all

# ------- Gadget

norm:
	-@norminette $(SRC_PATH)
	-@norminette $(INCLUDE)

push: fclean
	git add .
	git status
	git commit -m $(NAME)
	git push

.PHONY:	 default mandatory clean fclean re norm push
