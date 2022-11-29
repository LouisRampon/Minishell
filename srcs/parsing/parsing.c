/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:46:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/29 14:41:10 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char **ft_trim_quote(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i][0] == '\"' && strs[i][ft_strlen(strs[i]) - 1] == '\"')
			strs[i] = ft_substr(strs[i], 1, ft_strlen(strs[i]) - 2);
		i++;
	}
	return (strs);
}
char **ft_str_to_arg(char *str)
{
	char **temp;
	
	printf("str = %s\n", str);
	temp = ft_split_quote(str, ' ');
	return(ft_trim_quote(temp));
	return(ft_split(str, ' '));
}


t_command *ft_fill_cmd(char *str, size_t i)
{
	t_command *cmd;
	
	(void)i;
	cmd = malloc(sizeof(t_command));
	cmd->fd_in = ft_fd_in(str);
	cmd->fd_out = ft_fd_out(str);
	str = ft_clean_str(str);
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
	size_t j = 0;
	t_command *temp;
	
	i = 0;
	previous = NULL;
	new = NULL;
	if (check_syntax(str))
		return (0);
	str = replace_var(str, env);
	nb_cmd = nb_pipe(str) + 1;
	arg = ft_split_quote(str, '|');
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
	temp = head;
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
	return (head);
}
