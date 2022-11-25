# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 11:47:12 by lorampon          #+#    #+#              #
#    Updated: 2022/11/25 15:12:30 by lorampon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_PARSING_WITHOUT_PATH =	main.c\
						signal.c\
						parsing.c \
						check_synthax.c \
						replace_var.c \
						parsing_help.c \
						clean_function.c\
						manage_fd.c\

SRCS_ENV_WITHOUT_PATH = ft_add_env.c \
						ft_del_env.c\
						ft_env_get.c\
						ft_env_list_to_tab.c \
						ft_init_env_list.c										
									
SRCS_BUILT_IN_WITHOUT_PATH =	cd.c					\
								exit.c					\
								echo.c					\
								env.c					\
								export.c				\
								unset.c					\
								pwd.c					
				
SRCS_EXEC_WITHOUT_PATH =	ft_check_cmd.c				\
							ft_exec_built_in.c			\
							ft_exec_loop.c				
							
SRCS_UTILS_WITHOUT_PATH =	ft_perror.c					\
							ft_perror_exit.c			\
							arena_storage_pool.c		\
							ft_alloc.c					

OBJS_SRCS_PARSING_WITHOUT_PATH = $(SRCS_PARSING_WITHOUT_PATH:.c=.o)
OBJS_SRCS_ENV_WITHOUT_PATH = $(SRCS_ENV_WITHOUT_PATH:.c=.o)
OBJS_SRCS_EXEC_WITHOUT_PATH = $(SRCS_EXEC_WITHOUT_PATH:.c=.o)
OBJS_SRCS_UTILS_WITHOUT_PATH = $(SRCS_UTILS_WITHOUT_PATH:.c=.o)
OBJS_SRCS_BUILT_IN_WITHOUT_PATH = $(SRCS_BUILT_IN_WITHOUT_PATH:.c=.o)

HEADER_WITHOUT_PATH = minishell.h

PATH_TO_SRCS_PARSING = ./srcs/parsing/
PATH_TO_SRCS_ENV = ./srcs/env/
PATH_TO_SRCS_EXEC = ./srcs/exec/
PATH_TO_SRCS_UTILS = ./srcs/utils/
PATH_TO_OBJS = ./objs/
PATH_TO_HEADER = ./includes/
PATH_TO_LIB_DIR = ./libft/
PATH_TO_SRCS_BUILT_IN = ./srcs/built_in/

SRCS_PARSING = $(addprefix $(PATH_TO_SRCS_PARSING), $(SRCS_PARSING_WITHOUT_PATH))
SRCS_ENV= $(addprefix $(PATH_TO_SRCS_ENV), $(SRCS_ENV_WITHOUT_PATH))
SRCS_EXEC = $(addprefix $(PATH_TO_SRCS_EXEC), $(SRCS_EXEC_WITHOUT_PATH))
SRCS_UTILS = $(addprefix $(PATH_TO_SRCS_UTILS), $(SRCS_UTILS_WITHOUT_PATH))
SRCS_BUILT_IN = $(addprefix $(PATH_TO_SRCS_BUILT_IN), $(SRCS_BUILT_IN_WITHOUT_PATH))

OBJS_SRCS_PARSING = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_PARSING_WITHOUT_PATH))
OBJS_SRCS_ENV = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_ENV_WITHOUT_PATH))
OBJS_SRCS_EXEC = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_EXEC_WITHOUT_PATH))
OBJS_SRCS_UTILS = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_UTILS_WITHOUT_PATH))
OBJS_SRCS_BUILT_IN = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_BUILT_IN_WITHOUT_PATH))


OBJS =	$(OBJS_SRCS_PARSING) \
		$(OBJS_SRCS_ENV) \
		$(OBJS_SRCS_EXEC) \
		$(OBJS_SRCS_UTILS) \
		$(OBJS_SRCS_BUILT_IN)
		
HEADER =	$(addprefix $(PATH_TO_HEADER), $(HEADER_WITHOUT_PATH))

	######### COMMANDS ###########
CC = gcc
CFLAGS	= -Wall -Wextra -Werror
RM = rm -rf
READLINE_LIB = -lreadline
READLINE_HOMEBREW_LIB = -L ~/.brew/opt/readline/lib
READLINE_HOMEBREW_INCLUDE = -I ~/.brew/opt/readline/include
PATH_TO_LIBFT = ./libft/
LIBFT_A = $(PATH_TO_LIBFT)libft.a
	################################

	####### COLORS FOR PRINTF #######
GREEN 		= \033[0;32m
RED			= \033[0;91m
YELLOW      = \033[0;93m
WHITE       = \033[1;49;97m
	#################################
	
all: rcs $(PATH_TO_OBJS) $(NAME)
	printf "$(GREEN) $(NAME) is up to date$(WHITE)\n" 

$(PATH_TO_OBJS):
	mkdir -p ./objs/

# $(LIBFT_A): rsc
	
$(OBJS_SRCS_PARSING):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_PARSING)%.c Makefile $(HEADER) 
	printf "\033[2K\r$(YELLOW) Compiling:$(WHITE) $<"
	$(CC) $(CFLAGS) $(READLINE_HOMEBREW_INCLUDE) -c $< -o $@
	
$(OBJS_SRCS_ENV):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_ENV)%.c Makefile $(HEADER) 
	printf "\033[2K\r$(YELLOW)Compiling:$(WHITE) $< "
	$(CC) $(CFLAGS) -c $< -o $@
	

$(OBJS_SRCS_EXEC):$(PATH_TO_OBJS)%.o : $(PATH_TO_SRCS_EXEC)%.c Makefile $(HEADER) 
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJS_SRCS_UTILS):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_UTILS)%.c Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)Compiling:$(WHITE) $< "
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_SRCS_BUILT_IN):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS_BUILT_IN)%.c Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)Compiling:$(WHITE) $< "
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS) $(LIBFT_A)
	printf "\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(READLINE_LIB) $(READLINE_HOMEBREW_LIB) -o $(NAME)

rcs: 
	make -C $(PATH_TO_LIB_DIR)

git: fclean
	git add *
	git add -u
	git commit
	
clean:
	make fclean -C $(PATH_TO_LIB_DIR)
	$(RM) $(PATH_TO_OBJS)
	printf "$(RED) Files has been deleted in $(PATH_TO_OBJS) ($(NAME))$(WHITE)\n" 
	printf "$(GREEN) Clean $(WHITE)\n" 
	
fclean: clean
	$(RM) $(NAME)
	printf "$(RED) $(NAME) has been deleted$(WHITE)\n" 
	
re: fclean all

.PHONY: all rcs git clean fclean re
.SILENT: