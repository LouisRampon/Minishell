/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:30:06 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/03 15:57:14 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// typedef struct s_list
// {
// 	char			*str;
// 	struct s_list	*next;
// }	t_list;

void	ft_ctrl_c(int signal);
int 	rl_replace_line(const char *text, int clear_undo);

int		ft_parsing(char *str, char **env);


#endif