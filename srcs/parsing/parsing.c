/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:46:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/25 15:14:08 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char **ft_str_to_arg(char *str)
{
	char *temp;
	size_t		len;

	len = ft_strlen_to_c(str, '|');
	temp = ft_substr(str, 0, len);
	return(ft_split(temp, ' '));
}


t_command *ft_fill_cmd(char *str, size_t i)
{
	t_command *cmd;
	
	(void)i;
	cmd = malloc(sizeof(t_command));
	cmd->fd_in = ft_fd_in(str);
	cmd->fd_out = ft_fd_out(str);
	str = ft_clean_str(str);
	//printf("str before arg = %s\n", str);
	cmd->cmd = ft_str_to_arg(str);
	cmd->next = NULL;
	return (cmd);
}

t_command	*ft_parsing(char *str, char **env, t_command *head)
{
	t_command *previous;
	t_command *new;
	char	**arg;
	size_t nb_cmd;
	size_t	i;
	
	i = 0;
	previous = NULL;
	new = NULL;
	if (check_syntax(str))
		return (0);
	str = replace_var(str, env);
	nb_cmd = nb_pipe(str) + 1;
	arg = ft_split(str, '|');
	while (i < nb_cmd)
	{
		new = ft_fill_cmd(arg[i], i);
		if (previous)
			previous->next = new;
		else
			head = new;
		previous = new;
		i++;
	}
	return (head);
}