/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:30:06 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/24 15:27:28 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	int					fd_in;
	int					fd_out;
	char				**cmd;
	char 				*path;
	struct s_command	*next;
}t_command;

void	ft_ctrl_c(int signal);
int 	rl_replace_line(const char *text, int clear_undo);

t_command	*ft_parsing(char *str, char **env, t_command *head);
int		check_syntax(char *str);
int		check_double_pipe(char *str);

size_t	ft_strlen_to_c(char *str, char c);
size_t	ft_strlen_alnum(char *str);
size_t nb_pipe(char *str);

char *ft_clean_str(char *str);

int	ft_fd_out(char *str);
int	ft_fd_in(char *str);

char	*find_var_name(char *str, int i);
char	*replace_var_help(char *var_name, char **env);
char 	*ft_fill_final(char *str, char *var, int size, int i);
char	*replace_var(char *str, char **env);

//strlen pour fd et pour variable env
// < in abc > out > in | truc bidule | alal
#endif