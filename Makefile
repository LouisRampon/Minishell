# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 12:27:53 by lorampon          #+#    #+#              #
#    Updated: 2022/11/03 15:46:36 by lorampon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = \
				main.c\
				signal.c\
				parsing.c

OBJS_NAME = $(SRCS:.c=.o)

OBJS = $(addprefix $(OBJ_DIR),$(OBJS_NAME))
LIB_DIR = libft/
OBJ_DIR = objs/
SRC_DIR = srcs/

CC = gcc 
RM = rm -rf
READLINE_FLAGS = -lreadline -L ~/.brew/opt/readline/lib
FLAGS = -Wall -Wextra -Werror -g

all: rcs $(OBJ_DIR) $(NAME)
	printf "Cest compile"

$(NAME) : $(OBJS) includes/minishell.h Makefile libft/libft.a
	make -C $(LIB_DIR)
	$(CC) -o $(NAME) $(OBJS) -L $(LIB_DIR) -lft $(READLINE_FLAGS)
	echo "##### minishell compiling finished! #####"

rcs: 
	make -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	echo "##### Creating" [ $@ ] " #####"
	gcc $(FLAGS) -o $@ -c $<

clean:
	make -C $(LIB_DIR) clean --silent
	$(RM) $(OBJS) $(OBJ_DIR)
	echo "##### Removed object files #####"

fclean: clean
	make -C $(LIB_DIR) fclean --silent
	$(RM) $(NAME)
	echo "##### Removed binary files #####"

re : fclean all

git: fclean
	git add *
	git add -u
	git commit
	
.PHONY: all clean fclean leaks re

.SILENT: