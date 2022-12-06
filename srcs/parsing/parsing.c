/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:46:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/06 17:53:21 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char **ft_str_to_arg(char *str, t_shell *shell)
{
	char **temp;
	
	temp = ft_split_cmd(str, ' ', shell->arena);
	return(temp);
}


t_command *ft_fill_cmd(char *str, t_shell *shell)
{
	t_command *cmd;
	
	if (!str)
		return (NULL);
	cmd = ft_alloc(sizeof(t_command), shell->arena);
	if (!cmd)
		return (NULL);
	cmd->fd_in = ft_fd_in(str, shell);
	if (cmd->fd_in == -1)
		return (NULL);
	cmd->fd_out = ft_fd_out(str, shell);
	if (cmd->fd_out == -1)
		return (NULL);
	str = ft_clean_str(str);
	str = replace_var(str, shell);
	cmd->cmd = ft_str_to_arg(str, shell);
	if (!cmd->cmd)
		return (NULL);
	cmd->next = NULL;
	return (cmd);
}

t_shell	ft_parsing(char *str, t_shell *shell)
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
	{
		//printf("ici\n");
		return (*shell);
	}
	nb_cmd = nb_pipe(str) + 1;
	arg = ft_split_quote(str, '|', shell->arena);
	while (i < nb_cmd)
	{
		new = ft_fill_cmd(arg[i], shell);
		if (!new)
			return (*shell);
		if (previous)
			previous->next = new;
		else
			shell->cmd = new;
		previous = new;
		i++;
	}
	return (*shell);
}
