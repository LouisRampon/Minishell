/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:46:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/06 13:18:12 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char **ft_str_to_arg(char *str, t_shell *shell)
{
	char **temp;
	
	temp = ft_split_cmd(str, ' ', shell->arena);
	return(temp);
}


t_command *ft_fill_cmd(char *str, size_t i, t_shell *shell)
{
	t_command *cmd;
	
	(void)i;
	if (!str)
		return (NULL);
	cmd = ft_alloc(sizeof(t_command), shell->arena);
	cmd->fd_in = ft_fd_in(str, shell);
	if (cmd->fd_in == -1)
		return (NULL);
	cmd->fd_out = ft_fd_out(str, shell);
	if (cmd->fd_out == -1)
		return (NULL);
	str = ft_clean_str(str);
	str = replace_var(str, shell);
	cmd->cmd = ft_str_to_arg(str, shell);
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
	size_t j = 0;
	t_command *temp;
	
	i = 0;
	previous = NULL;
	new = NULL;
	if (check_syntax(str))
		return (*shell);
	nb_cmd = nb_pipe(str) + 1;
	arg = ft_split_quote(str, '|', shell->arena);
	while (i < nb_cmd)
	{
		new = ft_fill_cmd(arg[i], i, shell);
		if (previous)
			previous->next = new;
		else
			shell->cmd = new;
		previous = new;
		i++;
	}
	if (shell->cmd)
	{
	temp = shell->cmd;
	i = 0;
	while (temp->next)
	{
		printf("command %zu:\n", i);
		while(temp->cmd[j])
		{
			printf("word[%zu] = %s\n", j, temp->cmd[j]);
			j++;
		}
		j = 0;
		printf("fd_in = %d\n", temp->fd_in);
		printf("fd_out = %d\n", temp->fd_out);
		i++;
		temp = temp->next;
	}
	printf("command %zu:\n", i);
	while(temp->cmd[j])
	{
		printf("word[%zu] = %s\n", j, temp->cmd[j]);
		j++;
	}
	j = 0;
	printf("fd_in = %d\n", temp->fd_in);
	printf("fd_out = %d\n", temp->fd_out);
	}
	return (*shell);
}
