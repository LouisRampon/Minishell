# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 12:27:53 by lorampon          #+#    #+#              #
#    Updated: 2022/11/24 14:23:31 by lorampon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREY=$'\x1b[30m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m
NAME = minishell

SRCS = \
				main.c\
				signal.c\
				parsing.c \
				check_synthax.c \
				replace_var.c \
				parsing_help.c \
				clean_function.c\
				manage_fd.c

OBJS_NAME = $(SRCS:.c=.o)

OBJS = $(addprefix $(OBJ_DIR),$(OBJS_NAME))
LIB_DIR = libft/
OBJ_DIR = objs/
SRC_DIR = srcs/

CC = gcc 
RM = rm -rf
READLINE_FLAGS = -lreadline -L ~/.brew/opt/readline/lib
FLAGS = -Wall -Wextra -Werror

all: rcs $(OBJ_DIR) $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L $(LIB_DIR) -lft $(READLINE_FLAGS) -fsanitize=address
	printf "\n"
	

rcs: 
	make -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/minishell.h Makefile libft/libft.a	
	gcc $(FLAGS) -o $@ -c $<
	printf "\033[2K\r$(YELLOW)Compiling:$(WHITE) $< "


clean:
	make fclean -C $(LIB_DIR)
	$(RM) $(OBJS) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re : fclean all

git: fclean
	git add *
	git add -u
	git commit
	
.PHONY: all clean fclean leaks re

.SILENT: